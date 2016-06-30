#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <sstream>
#include "final_hash.h"

using namespace std;

FILE *opening;

int hasEOF = 0;
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, opening)) == buf) {
            hasEOF = 1;
            N=1<<20;
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
    while((c = readchar()) != '\t'){
        if(c == EOF) return 0;
        (*x) += c;
    }
    return 1;
}

int ReadInt(long long int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(NULL);
    freopen(argv[1],"w",stdout);
    char filepath[] = "/tmp2/dsa2016_project/2gm.small.txt";
    for(int gy=0;gy<4;gy++){
        hasEOF=0;
        //cerr<<filepath<<"\n";
        opening = fopen(filepath,"r");
        filepath[22]++;
        int corr = 0;
        while (hasEOF==0) {
            string x;
            if(ReadString(&x)==0) break;
            int len = x.length();
            //istringstream in(x);
            int co = 1;
            int ptr = 0;
            //string temp[1000];
            int cou = 0;
            cout<<x<<'\n'<<len<<'\n'<<hashing(x)<<'\n';
            corr++;
            long long int y = 0;
            ReadInt(&y);
            cout<<y<<'\n';

        }
        fclose(opening);
        //cerr<<corr<<'\n';
    }
    return 0;
}
