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

int yee;
stack <int> stk;
int popped = 0;
int sequence[50];
void rec(int n,int ptr,int next){
    if(ptr==yee){
        for(int g=0;g<yee;g++){
            printf("%d",sequence[g]);
            if(g!=yee-1) printf(" ");
        }
        printf("\n");
        return;
    }


    if(!stk.empty()){
        int temp = stk.top();
        sequence[ptr] = stk.top();
        stk.pop();
        rec(n-1,ptr+1,next);
        stk.push(temp);
    }

    if(next<=yee){
        stk.push(next);
        rec(n-1,ptr,next+1);
        stk.pop();
    }
    return;
}
int main(){
    scanf("%d",&yee);
    rec(yee*2,0,1);


}
