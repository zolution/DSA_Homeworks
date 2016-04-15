#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

int n,m;
int hor[50][50];
int hor_ptr[50];
int hor_done[50];
int hor_sum[50];
int ver[50][50];
int ver_ptr[50];
int ver_sum[50];
int board[50][50];

void input_data(){
    cin>>n>>m;
    char buf[1024];
    for(int h=0;h<n;h++){
        fgets(buf,1024,stdin);
        int len = strlen(buf);
        if(len<=1){
            h--;
            continue;
        }
        int ptr=0;
        int temp = 0;
        while(ptr<len){
            if(buf[ptr]>='0' && buf[ptr]<='9'){
                temp*=10;
                temp+=(buf[ptr]-'0');
            }
            else if(temp>0){
                hor[h][hor_ptr[h]]=temp;
                hor_sum[h]+=temp;
                hor_ptr[h]++;
                temp=0;
            }
            ptr++;
        }
    }
    for(int h=0;h<m;h++){
        fgets(buf,1024,stdin);

        int len = strlen(buf);
        if(len<=1){
            h--;
            continue;
        }
        int ptr=0;
        int temp = 0;
        while(ptr<len){
            if(buf[ptr]>='0' && buf[ptr]<='9'){
                temp*=10;
                temp+=(buf[ptr]-'0');
            }
            else if(temp>0){
                ver[h][ver_ptr[h]]=temp;
                ver_sum[h]+=temp;
                ver_ptr[h]++;
                temp=0;
            }
            ptr++;
        }
    }
    return;
}

void print_board(){
    for(int h=0;h<n;h++){
        for(int i=0;i<m;i++){
            printf("%c",board[h][i]>0?'#':'.');
        }
        printf("\n");
    }
}

int co_saved[51][51];
int ptr_saved[51][51];
int prev_saved[51][51];
int diff_saved[51][51];
bool saved_true[51][51];
int ver_check(int index,int ver_limit,int beginn){
    for(int g=beginn;g<=ver_limit;g++){
        int total = ver_sum[g]+ver_ptr[g]-1;
        int diff = n-total;
        int prev = board[0][g];
        int ptr = 0;
        int co = (board[0][g]>0 ? 1 : 0);
        if(index==0){
            if(board[0][g]==0 && diff==0) return false;
        }
        for(int h=max(1,index);h<=min(index,n-1);h++){
            //saved_true[g][h]=false;
            //if(h>1 && (!saved_true[g][h-1])) return g;
            //saved_true[g][h]=false;
            if(h>1){
                co=co_saved[g][h-1];
                ptr=ptr_saved[g][h-1];
                prev=prev_saved[g][h-1];
                diff=diff_saved[g][h-1];
            }
            if(h==1){
                co=(board[h-1][g]==0)?0:1;
                ptr=0;
                prev=board[h-1][g];
                diff=n-total+(board[h-1][g]-1);
                co_saved[g][h-1]=co;
                ptr_saved[g][h-1]=ptr;
                prev_saved[g][h-1]=prev;
                diff_saved[g][h-1]=diff;
            }


            /*if(board[h][g]!=2 && board[h][g]!=-2 && h>index) board[h][g]=0;
            if(board[h][g]==0){
                if(prev>0 && co<ver_ptr[g]) co++;
                else if(prev>0 && co==ver[g][ptr]){
                    ptr++;
                    co=0;
                }
                else break;
                if(ptr==ver_ptr[g]){
                    for(int y=h+1;y<=n-1;y++) if(board[y][g]==2) return false;
                    break;
                }
            }*/
            if((prev == 0 && board[h][g]==0) || (prev == 1 && board[h][g]==1)){
                if(board[h][g]>0) co++;
                if((board[h][g]>0) && co>ver[g][ptr]) return g;
                if(board[h][g]==0) diff--;
                if(diff<0) return g;
            }
            else{
                if(board[h][g]>0){
                    if(ptr>=ver_ptr[g]) return g;
                    co=1;
                }
                else{
                    if(co != ver[g][ptr]) return g;
                    co=0;
                    ptr++;
                }
                prev=board[h][g];
            }
            if(ptr>=ver_ptr[g] && co>0) return g;
            //saved_true[g][h]=true;
            co_saved[g][h]=co;
            ptr_saved[g][h]=ptr;
            prev_saved[g][h]=prev;
            diff_saved[g][h]=diff;

        }
    }
    //printf("ACCEPTED index %d\n",index);
    return -1;
}

vector <int> able[50];
int able_size[50];
int able_index_ptr[50];
int index_max = -1;
bool hor_dfs(int index,int hor_index,int remaining_space,int cur_pos){
    index_max = max(index,index_max);
    //printf("%d %d %d %d\n",index,hor_index,remaining_space,cur_pos);
    //print_board();
    //system("pause");
    if(index>=n) return true;
    if(hor_index == hor_ptr[index]){
        int check = ver_check(index,m-1,0);
        if(check!=-1){
            //printf("GG!! %d %d\n",index,check);
            //print_board();
            //system("pause");
            return false;
        }
        else{
            if(hor_dfs(index+1,0,0,0)) return true;
            return false;
        }
    }
    if(hor_index==0){

        able[index].clear();
        able_size[index]=0;
        able_index_ptr[index]=0;
        for(int start = cur_pos; start<m; start++) board[index][start] = 1;
        int a=cur_pos;
        able[index].push_back(-1);
        //printf("---pushing: index:%d\n---",index);
        while(a != -1){
            a = ver_check(index,m-1,a);
            if(a!=-1){
                able[index].push_back(a);
                //printf("%d ",a);
                able_size[index]++;
                a++;
            }
        }
        //printf("-----end of print-----\n");
        able[index].push_back(m);
        able_size[index]+=2;
        for(int start = cur_pos; start<m; start++) board[index][start] = 0;
        //printf("YA!\n");
    }
    while(cur_pos>=able[index][able_index_ptr[index]+1]){
        if(cur_pos == able[index][able_index_ptr[index]+1]) cur_pos++;
        able_index_ptr[index]++;
    }
    int start = max(cur_pos,able[index][able_index_ptr[index]]+1);
    while(able_index_ptr[index] < able_size[index]-1){
        if(start < (able[index][able_index_ptr[index]]-hor[index][hor_index]+1)){
            start = max(cur_pos,able[index][able_index_ptr[index]+1]+1);
            able_index_ptr[index]++;
            continue;
        }
        for(int q = start; q<(start + hor[index][hor_index]);q++) board[index][q] = 1;
        //printf("!!!%d %d %d %d %d %d\n",index,hor_index,able_index_ptr[index],cur_pos,start,(able[index][able_index_ptr[index]+1]-hor[index][hor_index]+1));
        for(int q = start; q<(able[index][able_index_ptr[index]+1]-hor[index][hor_index]+1);q++){
            board[index][q+hor[index][hor_index]-1] = 1;
            int temprr = able_index_ptr[index];
            if(hor_dfs(index,hor_index+1,remaining_space,q+hor[index][hor_index]+1)) return true;
            able_index_ptr[index] = temprr;
            board[index][q] = 0;
        }
        for(int q = max(cur_pos,able[index][able_index_ptr[index]+1]-hor[index][hor_index]+1) ; q<=able[index][able_index_ptr[index]+1];q++) board[index][q]=0;
        start = max(cur_pos,able[index][able_index_ptr[index]+1]+1);
        able_index_ptr[index]++;
    }
    return false;
}

int main(){
    input_data();
    int total = hor_sum[0]+hor_ptr[0]-1;
    int diff = m-total;
    hor_dfs(0,0,0,0);
    print_board();
    //printf("%d\n",index_max);
    return 0;
}
