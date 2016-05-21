#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

struct node{
    int val;
    node* next;
};
FILE *fp;
string dict[150000];

node hash_table[1<<26];
const int mod = 19970701;
const int mul = 97;
const int mod2 = 431253;
const int mul2 = 79;

int absr(int a){
    if(a<0) return -a;
    return a;
}

int hashing2(string s){
    int val = 0;
    int len = s.length();
    for(int g=0;g<len;g++){
        val*=mul2;
        val+=(int)s[g];
        val = val % mod2;
    }
    return val;
}

int hashing(string s){
    int val = 0;
    int len = s.length();
    int yee = 0;
    for(int g=0;g<len;g++){
        val*=mul;
        val+=(int)s[g];
        yee ^= (int)s[g];
        val = val % mod;
    }
    int val2 = 0;
    return (val+3*val2)%mod;
}

void build_dict(){
    fp = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b","r");
    for(int f=0;f<(1<<26);f++){
        hash_table[f].val = -1;
        hash_table[f].next = NULL;
    }
    char temp_str[1<<16];
    int ptr = 0;
    int crash_co=0;
    while(fgets(temp_str,1<<16,fp) != NULL){
        int ptr2=0;
        while(1){
            if(temp_str[ptr2]==' ' || temp_str[ptr2]=='\t' || temp_str[ptr2]=='\0' || temp_str[ptr2]=='\n')break;
            if(temp_str[ptr2]>='A' && temp_str[ptr2]<='Z') temp_str[ptr2] = temp_str[ptr2]-'A'+'a';
            dict[ptr]+=temp_str[ptr2];
            ptr2++;
        }
        int hash_result = hashing(dict[ptr]);
        if(hash_table[hash_result].val != -1){
            crash_co++;
            node* temp = new node();
            temp->val = ptr;
            temp->next = NULL;
            node* temp2 = &hash_table[hash_result];
            while(temp2->next!=NULL) temp2 = temp2->next;
            temp2->next = temp;
        }
        else{
            hash_table[hash_result].val = ptr;
        }
        ptr++;
    }
}

bool finding(string s){
    int hash_result = hashing(s);
    if(hash_table[hash_result].val==-1) return false;
    else{
        node* temp = &hash_table[hash_result];
        do{
            if(dict[temp->val] == s) return true;
        }while(temp->next!=NULL && (temp=(temp->next)));
        return false;
    }
}

vector <string> vec;

void ed(string s,int dist){
    if(dist >= 3) return;
    int len = s.length();
    //insert
    for(int g=0;g<=len;g++){
        for(int h='a';h<='z';h++){
            string temp = s;
            temp.insert(g,1,h);
            if(finding(temp)) vec.push_back(temp);
            ed(temp,dist+1);
        }
    }
    //delete
    for(int g=0;g<len;g++){
        string temp = s;
        temp.erase(temp.begin()+g);
        if(finding(temp)) vec.push_back(temp);
        ed(temp,dist+1);
    }
    //replace
    for(int g=0;g<len;g++){
        for(int h='a';h<='z';h++){
            string temp = s;
            temp.replace(g,1,1,h);
            if(finding(temp)) vec.push_back(temp);
            ed(temp,dist+1);
        }
    }
    //switch
    for(int g=0;g<len-1;g++){
        string temp = s;
        swap(temp[g],temp[g+1]);
        if(finding(temp)) vec.push_back(temp);
        ed(temp,dist+1);
    }
    return;
}

int main(){
    build_dict();
    char temp_str[1<<16];
    string current;
    while(fgets(temp_str,1<<16,stdin) != NULL){
        vec.clear();
        current="";
        int ptr2=0;
        while(1){
            if(temp_str[ptr2]==' ' || temp_str[ptr2]=='\t' || temp_str[ptr2]=='\0' || temp_str[ptr2]=='\n') break;
            current+=temp_str[ptr2];
            ptr2++;
        }
        cout<<current<<" ==>";
        if(finding(current)) printf(" OK");
        else{
            ed(current,1);
            if(vec.begin()==vec.end()){
                printf(" NONE");
            }else{
                sort(vec.begin(),vec.end());
                auto it = unique(vec.begin(),vec.end());
                vec.resize(distance(vec.begin(),it));
                auto beg = vec.begin();
                auto fin = vec.end();
                for(auto r = beg; r!=fin ; ++r){
                    cout<<" "<<*r;
                }
            }
        }
        printf("\n");
    }
    return 0;
}
