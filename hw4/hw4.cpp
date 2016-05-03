#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <cstring>
#include <stack>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;
class data;

priority_queue <data> buy;
priority_queue <data> sell;
bool canceled[50000000];

class data{
private:
    int bidId;
    int clientId;
    int action;
    int price;
    int shareCount;

public:
    data(int a,int b,int c,int d,int e){
        bidId=a;
        clientId=b;
        action=c;
        price=d;
        shareCount=e;
    }
    ~data(){}
    bool operator <(const data& b)const{
        if(action==0){
            if(price!=b.price) return price<b.price;
            else return bidId>b.bidId;
        }
        if(action==1){
            if(price!=b.price) return price>b.price;
            else return bidId>b.bidId;
        }
    }
    int get_price()const{return price;}
    int get_bidID()const{return bidId;}
    int get_clientID()const{return clientId;}
    int get_shareCount()const{return shareCount;}
    void push(){
        if(action==0) buy.push(*this);
        if(action==1) sell.push(*this);
    }
    void distract(int no){
        shareCount-=no;
    }
};


int main(){
    int a,b,c,d,e;
    int transId=0;
    while(scanf("%d %d %d %d %d",&a,&b,&c,&d,&e)!=EOF){
        if(c==2){
            canceled[d]=true;
            continue;
        }
        data temp(a,b,c,d,e);
        temp.push();
        while(!buy.empty() && !sell.empty() && buy.top().get_price()>=sell.top().get_price()){
            if(canceled[buy.top().get_bidID()]) {buy.pop(); continue;}
            if(canceled[sell.top().get_bidID()]) {sell.pop(); continue;}
            int minn = min(buy.top().get_shareCount(),sell.top().get_shareCount());
            printf("%d\t%d\t%d\t%d\t%d\n", transId++, buy.top().get_clientID() ,sell.top().get_clientID() ,sell.top().get_price(), minn);
            data temp = buy.top();
            buy.pop();
            temp.distract(minn);
            if(temp.get_shareCount()>0) temp.push();
            temp = sell.top();
            sell.pop();
            temp.distract(minn);
            if(temp.get_shareCount()>0) temp.push();
        }
    }

}
