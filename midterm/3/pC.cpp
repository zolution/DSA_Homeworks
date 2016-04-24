#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>

//#include <bits/stdc++.h>
using namespace std;

int tree[1100000];
int pre[1100000];
int post[1100000];
int tptr = 0;

void input(){
    char buf[1024];
    for(int h=0;h<1;h++){
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
                pre[tptr]=temp;
                tptr++;
                temp=0;
            }
            ptr++;
        }
    }
    tptr = 0;
    for(int h=0;h<1;h++){
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
                post[tptr]=temp;
                tptr++;
                temp=0;
            }
            ptr++;
        }
    }
}
int pre_pos = 0;
void tree_construct(int tree_pos,int post_start,int post_end){
    //printf("%d %d %d %d\n",tree_pos,post_start,post_end,pre[pre_pos]);
    if(pre_pos >= tptr){
        //printf("!!\n");
        return;
    }
    tree[tree_pos] = pre[pre_pos];
    if(post_start == post_end || post_start+1 == post_end){
        pre_pos++;
        return;
    }
    int temp=0;
    if(pre_pos == tptr-1) return;
    for(int g=post_start;g<post_end;g++){
        if(post[g]==pre[pre_pos+1]){
            temp = g;
            break;
        }
    }
    //if(temp == 0) return;
    pre_pos++;
    tree_construct(2*tree_pos,post_start,temp);
    tree_construct(2*tree_pos+1,temp+1,post_end);
    return;

}

int main(){
    for(int y=0;y<1100000;y++) tree[y]=-1;
    input();

    /*for(int g=0;g<tptr;g++){
        printf("%d\n",pre[g]);
    }
    for(int g=0;g<tptr;g++){
        printf("%d\n",post[g]);
    }*/
    tree_construct(1,0,tptr);
    int max_pos = 0;


    for(int f=0;f<1100000;f++){
        if(tree[f]!=-1) max_pos = f;
    }
    for(int g=0;g<=max_pos;g++){
        printf("%d",tree[g]);
        if(g!=max_pos) printf(" ");
    }
    printf("\n");

}
