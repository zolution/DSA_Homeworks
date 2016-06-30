#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#include "final_hash.h"

using namespace std;

FILE *opening;
const string preposition[20] = {"of","to","in","for","with","on","at","by","from","up","about","than","after","before","down","between","under","since","without","near"};
int hasEOF = 0;
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, opening)) == buf) {
            hasEOF = 1;
            N=1<<16;
            memset(buf,0,sizeof(buf));
            p = buf;
            end = buf;
            //p = buf;
            return EOF;
        }
        p = buf;
    }
    return *p++;
}

int ReadString(string *x) {
    char c, neg;
    while((c = readchar()) != '\n'){
        if(c == EOF) return 0;
        (*x) += c;
    }
    return 1;
}

int ReadInt(int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

struct table_node{
    int index = -1;
    int len;
    int freq;
    table_node *next = NULL;
};

struct string_node{
    string voc;
    string_node *next;
};

table_node hash_table[4][8000000];
string dict[42000000];

const int amount[4] = {8430018,15960922,11765365,5773234};

void init(){
    int ptr=0;
    for(int h=0;h<4;h++){
        for(int i=0;i<amount[h];i++){
            //cerr<<"yee";
            ReadString(&dict[ptr]);
            int len;
            ReadInt(&len);
            int val;
            ReadInt(&val);
            int freq;
            ReadInt(&freq);
            if(hash_table[h][val].index != -1){
                table_node* temp = new table_node();
                temp->index = ptr;
                temp->len = len;
                temp->freq = freq;
                temp->next = NULL;
                table_node* temp2 = &hash_table[h][val];
                while(temp2->next!=NULL) temp2 = temp2->next;
                temp2->next = temp;
            }
            else{
                hash_table[h][val].index = ptr;
                hash_table[h][val].len = len;
                hash_table[h][val].freq = freq;
                hash_table[h][val].next = NULL;
            }
            ptr++;
        }
    }
}

bool isprepose(string test){
    for(int g=0;g<20;g++){
        if(test==preposition[g]) return true;
    }
    return false;
}

class candidate_struct{
    public:
        int freq;
        string data;
        candidate_struct(int f,string g){
            freq = f;
            data = g;
        }
        candidate_struct(){
            freq = 0;
            data = "";
        }
        ~candidate_struct(){}
        bool operator <(const candidate_struct& b)const{
            if(freq>b.freq) return true;
            else if( freq==b.freq && strcmp(data.c_str(),b.data.c_str())<0) return true;
            return false;
        }
        bool operator ==(const candidate_struct& b)const{
            if(freq==b.freq && data==b.data) return true;
            return false;
        }
        candidate_struct& operator=(const candidate_struct& a){
            freq = a.freq;
            data = a.data;
        }
};

int count_prepose[100];
int count_origin[100];
int total_len=0;
int ptr = 0;
string prepose[100][100];
string origin[100][100];
vector <string> candidate_set;
vector <int> candidate_set_voc_length;
bool last_is_prepose;

void generate_no_prepose(){
    //for(int re=0;re<total_len;re++) cout<<origin[0][re]<<endl;
    if(total_len>5) return;
    for(int h=0;h<=total_len;h++){
        string temp1="",temp2="";
        for(int i=0;i<h;i++){
            temp1 += origin[0][i];
            temp1 += ' ';
        }
        for(int j=h;j<total_len;j++){
            temp2 += origin[0][j];
            if(j!=total_len-1) temp2 += ' ';
        }
        if(total_len<=5 && h==0){
            candidate_set.push_back(temp1 + temp2);
            candidate_set_voc_length.push_back(total_len);
        }
        /*for(auto u:candidate_set){
            cout<<(u)<<endl;
        }*/
        if(total_len<=4){
            for(int g=0;g<20;g++){
                if(h!=total_len) candidate_set.push_back(temp1 + preposition[g] + " " + temp2);
                else candidate_set.push_back(temp1 + preposition[g]);
                candidate_set_voc_length.push_back(total_len+1);
            }
        }
        /*for(auto u:candidate_set){
            cout<<(u)<<endl;
        }*/
        if(total_len<=3){
            for(int h2=h;h2<=total_len;h2++){
                string temp4="",temp5="",temp6="";
                for(int i=0;i<h;i++){
                    temp4 += origin[0][i];
                    temp4 += ' ';
                }
                for(int j=h;j<h2;j++){
                    temp5 += origin[0][j];
                    temp5 += ' ';
                }
                for(int k=h2;k<total_len;k++){
                    temp6 += origin[0][k];
                    if(k!=total_len-1) temp6 += ' ';
                }
                for(int g=0;g<20;g++){
                    for(int y=0;y<20;y++){
                        if(h2!=total_len) candidate_set.push_back(temp4 + preposition[g] + " " + temp5 + preposition[y] + " " + temp6);
                        else candidate_set.push_back(temp4 + preposition[g] + " " + temp5 + preposition[y]);
                        candidate_set_voc_length.push_back(total_len+2);
                    }
                }
            }
        }
    }
    return;
}

void generate_prepose(){
    if(total_len>11) return;
    if(last_is_prepose) ptr++;
    string prepose_set[10][1000][10];
    int count_prepose_set[10][1000];
    int ptr_prepose[10];
    memset(ptr_prepose,0,sizeof(ptr_prepose));
    memset(count_prepose_set,0,sizeof(count_prepose_set));
    //cout<<"start_prepose_set\n";
    for(int h=0;h<ptr;h++){
        for(int r=0;r<20;r++){ // insert
            for(int g=0;g<=count_prepose[h];g++){
                for(int i=0;i<count_prepose[h];i++){
                    prepose_set[h][ptr_prepose[h]][i+(i>=g?1:0)] = prepose[h][i];

                }
                prepose_set[h][ptr_prepose[h]][g] = preposition[r];
                count_prepose_set[h][ptr_prepose[h]] = count_prepose[h]+1;
                ptr_prepose[h]++;
            }
        }
        for(int g=0;g<count_prepose[h];g++){ //delete
            for(int i=0;i<count_prepose[h];i++){
                if(i==g) continue;
                prepose_set[h][ptr_prepose[h]][count_prepose_set[h][ptr_prepose[h]]] = prepose[h][i];
                count_prepose_set[h][ptr_prepose[h]]++;
            }
            ptr_prepose[h]++;
        }
        for(int r=0;r<20;r++){ //substitute
            for(int g=0;g<count_prepose[h];g++){
                for(int i=0;i<count_prepose[h];i++){
                    if(i==g) prepose_set[h][ptr_prepose[h]][count_prepose_set[h][ptr_prepose[h]]] = preposition[r];
                    else prepose_set[h][ptr_prepose[h]][count_prepose_set[h][ptr_prepose[h]]] = prepose[h][i];
                    count_prepose_set[h][ptr_prepose[h]]++;
                }
                ptr_prepose[h]++;
            }
        }
    }
    int current_position[20];
    memset(current_position,0,sizeof(current_position));
    //cout<<"finish_prepose_set\n";
    while(current_position[0]<ptr_prepose[0]){
        string temp = "";
        int total_count_len = 0;
        for(int g=0;g<ptr+1;g++){ // try
            for(int h=0;h<count_origin[g];h++){
                if(total_count_len>0) temp+=" ";
                temp+=origin[g][h];
                if(origin[g][h]!="")total_count_len++;
            }
            if(total_count_len>5){temp="";break;}
            for(int i=0;i<count_prepose_set[g][current_position[g]];i++){
                if(total_count_len>0) temp+=" ";
                temp+=prepose_set[g][current_position[g]][i];
                if(prepose_set[g][current_position[g]][i]!="")total_count_len++;
            }
            if(total_count_len>5){temp="";break;}
        }
        if(!(temp=="")){
            //cout<<"!!"<<temp<<" "<<total_count_len<<'\n';
            candidate_set.push_back(temp);
            candidate_set_voc_length.push_back(total_count_len);
        }
        for(int r=ptr-1;r>=0;r--){
            if(current_position[r]+1<ptr_prepose[r]){
                current_position[r]++;
                break;
            }
            if(r==0) current_position[r]++;
            else current_position[r]=0;
        }
    }
    return;
}

int finding(string s,int voc_len){
    if(voc_len<=1 || voc_len>5) return -1;
    int hash_result = hashing(s);
    int len_of_s = s.length();
    if(hash_table[voc_len-2][hash_result].index==-1) return -1;
    else{
        table_node* temp = &hash_table[voc_len-2][hash_result];
        do{
            if(temp->len == len_of_s && dict[temp->index] == s) return temp->freq;
        }while(temp->next!=NULL && (temp=(temp->next)));
        return -1;
    }
}

int main(int argc, char** argv){
    std::ios::sync_with_stdio(NULL);
    opening = fopen(argv[1],"r");
    init();
    string query;
    //cout<<"rrr"<<endl;
    while(getline(cin,query)){
        candidate_set.clear();
        candidate_set_voc_length.clear();
        ptr = 0;
        last_is_prepose = false;

        memset(count_prepose,0,sizeof(count_prepose));
        memset(count_origin,0,sizeof(count_origin));
        total_len=0;
        istringstream in(query);
        string temp;
        while(in>>temp){
            total_len++;
            if(isprepose(temp)){
                prepose[ptr][count_prepose[ptr]] = temp;
                count_prepose[ptr]++;
                last_is_prepose = true;
            }
            else if(last_is_prepose){
                ptr++;
                origin[ptr][count_origin[ptr]] = temp;
                count_origin[ptr]++;
                last_is_prepose = false;
            }
            else{
                origin[ptr][count_origin[ptr]] = temp;
                count_origin[ptr]++;
            }
        }
        //cout<<"wow"<<endl;
        if(ptr==0 && last_is_prepose==false) generate_no_prepose();
        else generate_prepose();
        auto v=candidate_set_voc_length.begin();
        vector <candidate_struct> ans_candidate;
        candidate_struct ans[20];
        int ans_co = 0;
        for(auto u=candidate_set.begin();u!=candidate_set.end() && v!=candidate_set_voc_length.end();u++){
            //cout<<*u<<" "<<*v<<endl;
            int aim_freq = finding(*u,*v);
            //cout<<*u<<" "<<aim_freq<<" "<<*v<<'\n';
            if(aim_freq==-1){
                v++;
                continue;
            }
            else{
                ans_candidate.push_back(candidate_struct(aim_freq,*u));
            }
            v++;
        }
        sort(ans_candidate.begin(),ans_candidate.end());
        for(auto u:ans_candidate){
            if(ans_co>=10) break;
            if(ans_co > 0 && u==ans[ans_co-1]) continue;
            ans[ans_co] = u;
            ans_co++;
        }
        cout<<"query: "<<query<<'\n';
        cout<<"output: "<<ans_co<<'\n';
        for(int f=0;f<ans_co;f++){
            cout<<ans[f].data<<'\t'<<ans[f].freq<<'\n';
        }
    }
    return 0;
}
