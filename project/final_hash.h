#ifndef FINAL_HASH_H_INCLUDED
#define FINAL_HASH_H_INCLUDED

#include <cstring>

using namespace std;
const int mod = 7970783;
const int mul = 97;
const int mod2 = 431253;
const int mul2 = 79;

int absr(int a){
    if(a<0) return -a;
    return a;
}

int hashing(string s){
    int val = 0;
    int len = s.length();
    int yee = 0;
    for(int g=0;g<len;g++){
        val*=mul;
        val+=(int)s[g];
        //yee ^= (int)s[g];
        val = val % mod;
    }
    int val2 = 0;
    return (val+3*val2)%mod;
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

#endif // FINAL_HASH_H_INCLUDED
