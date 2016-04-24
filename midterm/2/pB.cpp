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

int tree[1000];

int first_1 = 0;
int first_2=0;
int first_3=0;
void preorder(int pos){
    if(tree[pos] == -1) return;
    if(first_1!=0) printf(" ");
    first_1 = 1;
    printf("%d",tree[pos]);
    preorder(pos*2);
    preorder(pos*2 + 1);
    return;
}

void inorder(int pos){
    if(tree[pos] == -1) return;
    inorder(pos*2);
    if(first_2!=0) printf(" ");
    first_2 = 1;
    printf("%d",tree[pos]);
    inorder(pos*2 + 1);
    return;
}

void postorder(int pos){
    if(tree[pos] == -1) return;
    postorder(pos*2);
    postorder(pos*2 + 1);
    if(first_3!=0) printf(" ");
    first_3 = 1;
    printf("%d",tree[pos]);
    return;
}

int main(){
    for(int g=0;g<1000;g++) tree[g] = -1;
    int ptr = 0;
    int temp;
    while(scanf("%d",&temp) != EOF){
        tree[ptr] = temp;
        ptr++;
    }
    preorder(1);
    printf("\n");
    inorder(1);
    printf("\n");
    postorder(1);
    printf("\n");

}
