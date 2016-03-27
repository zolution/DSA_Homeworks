#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int hasEOF = 0;
FILE *fp;

class data{
    public:
        int uid,iid;
        bool res;
        int time;
        data(int a,int b,int c,int d){
            uid = a;
            iid = b;
            res = (c==1)?true:false;
            time = d;
        }
        bool operator==(const data&);
};

bool data::operator==(const data& a){
    if((uid==a.uid && iid==a.iid && a.time==time)) return true;
    return false;
}

vector <data> item_vec;
vector <data> user[3000000];
int user_count[3000000];
vector <data>::iterator item_vec_end;

// input optimization by morris
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, fp)) == buf) {
            hasEOF = 1;
            return EOF;
        }
        p = buf;
    }
    return *p++;
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

void init(){
    item_vec.reserve(75000000);
    fill(user_count, user_count + 3000000, 0);
}

bool cmp_item_vec(data a,data b){
    if(a.iid != b.iid) return a.iid < b.iid;
    if(a.time != b.time) return a.time < b.time;
    if(a.uid != b.uid) return a.uid < b.uid;
    return false;
}

void accept(int u,int i,int t){
    data temp(u,i,true,t);
    auto pos = lower_bound(user[u].begin(),user[u].end(),temp,cmp_item_vec);
    if(pos!=user[u].end() && (*pos) == temp){
        if(pos->res) printf("1\n");
        else printf("-1\n");
    }
    else printf("0\n");
    return;
}

void items(int u1,int u2){
    auto ptr1 = user[u1].begin();
    auto ptr1e = user[u1].end();
    auto ptr2 = user[u2].begin();
    auto ptr2e = user[u2].end();
    bool flag = false;
	int prev = -1;
    while(true){
        if(ptr1 >= ptr1e || ptr2 >= ptr2e) break;
        if(ptr1-> iid == ptr2->iid){
            flag = true;
            if(prev!= ptr1->iid){
				printf("%d\n",ptr1->iid);
				prev = ptr1->iid;
			}
            ptr1++; ptr2++;
        }
        else (ptr1->iid > ptr2->iid) ? (ptr2++) : (ptr1++);
    }
    if(!flag) printf("EMPTY\n");
    return;
}

void users(int i1,int i2,int t1,int t2){
    vector <int> usr_i1;
    vector <int> usr_i2;
    data temp_i1(-1,i1,true,t1);
    auto i1_begin = lower_bound(item_vec.begin(),item_vec.end(),temp_i1,cmp_item_vec);
    while(i1_begin != item_vec_end && i1_begin->iid == i1 && i1_begin->time <= t2){
        usr_i1.push_back(i1_begin->uid);
        i1_begin++;
    }
    data temp_i2(-1,i2,true,t1);
    auto i2_begin = lower_bound(item_vec.begin(),item_vec.end(),temp_i2,cmp_item_vec);
    while(i2_begin != item_vec_end && i2_begin->iid == i2 && i2_begin->time <= t2){
        usr_i2.push_back(i2_begin->uid);
        i2_begin++;
    }
    sort(usr_i1.begin(),usr_i1.end());
    sort(usr_i2.begin(),usr_i2.end());
    //auto ptr1e = unique(usr_i2.begin(),usr_i2.end())+1;
    //auto ptr2e = unique(usr_i1.begin(),usr_i1.end())+1;
    vector<int> :: iterator ite;
    auto ptr1 = usr_i1.begin();
    auto ptr1e = usr_i1.end();
    auto ptr2 = usr_i2.begin();
    auto ptr2e = usr_i2.end();
	int prev = -1;
    bool flag = false;
    while(true){
        if(ptr1 >= ptr1e || ptr2 >= ptr2e) break;
        if(*ptr1 == *ptr2){
            flag = true;
            if(prev!=*ptr1){
				printf("%d\n",*ptr1);
				prev = *ptr1;
			}
            ptr1++; ptr2++;
        }
        else (*ptr1 > *ptr2) ? (ptr2++) : (ptr1++);
    }
    if(!flag) printf("EMPTY\n");
    return;
}

void ratio(int i,int threshold){
    int total = 0;
    int acc = 0;
    for(int h=0;h<3000000;h++){
        if(user_count[h] > threshold){
            total++;
            data aim(h,i,true,-1);
            auto ptr = lower_bound(user[h].begin(),user[h].end(),aim,cmp_item_vec);
            auto ptre = user[h].end();
            while(ptr != ptre && ptr->iid == i){
                if(ptr->res){
                    acc++;
                    break;
                }
                ptr++;
            }
        }
    }
    printf("%d/%d\n",acc,total);
    return;
}

vector <int> user_group;

void findtime_item(int i){
    vector <int> timestamp;
    bool flag = false;
    for(auto h:user_group){
        data aim(h,i,true,-1);
        auto ptr = lower_bound(user[h].begin(),user[h].end(),aim,cmp_item_vec);
        auto ptre = user[h].end();
        while(ptr != ptre && ptr->iid == i){
            timestamp.push_back(ptr->time);
            ptr++;
        }
    }
    sort(timestamp.begin(),timestamp.end());
    //auto it = unique(timestamp.begin(),timestamp.end());
	//timestamp.resize(distance(timestamp.begin(),it));
    if(timestamp.size() == 0) printf("EMPTY\n");
    else{
		int prev = -1;
        for(auto t:timestamp){	
			if(t!=prev){
				prev = t;
				printf("%d\n",t);
			}
		}
    }
    return;
}



int main(){
    init();
    fp = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt","r");
    int a,b,c,d;
    int pa=0,pb=0,pc=0,pd=0;
    while(ReadInt(&a) && ReadInt(&b) && ReadInt(&c) && ReadInt(&d)){
        if(a==pa && b==pb && c==pc && d==pd) continue;
		pa=a;pb=b;pc=c;pd=d;
        data temp(a,b,c,d);
        item_vec.push_back(temp);
        user[a].push_back(temp);
        user_count[a]++;
    }
    sort(item_vec.begin(),item_vec.end(),cmp_item_vec);
	//printf("%d\n",item_vec.size());
	unique(item_vec.begin(),item_vec.end());
	//printf("%d\n",item_vec.size());
    for(int g=0;g<3000000;g++){
        if(user[g].size() == 0) continue;
        sort(user[g].begin(),user[g].end(),cmp_item_vec);
    }
    item_vec_end = item_vec.end();

    int query;
    scanf("%d",&query);
    char com[64];
    bool flag = false;
    while(query--){
        if(!flag) scanf("%s",com);
        flag = false;
        if(com[0]=='a'){
            int u,i,t;
            scanf("%d %d %d",&u,&i,&t);
            accept(u,i,t);
        }
        if(com[0]=='i'){
            int u1,u2;
            scanf("%d %d",&u1,&u2);
            items(u1,u2);
        }
        if(com[0]=='u'){
            int i1,i2,t1,t2;
            scanf("%d %d %d %d",&i1,&i2,&t1,&t2);
            users(i1,i2,t1,t2);
        }
        if(com[0]=='r'){
            int a,b;
            scanf("%d %d",&a,&b);
            ratio(a,b);
        }
        if(com[0]=='f'){
            int i;
            scanf("%d",&i);
            flag = true;
            user_group.clear();
            while(scanf("%s",com) != EOF){
                if(!(com[0]<='9' && com[0]>='0')) break;
                user_group.push_back(atoi(com));
            }
            findtime_item(i);
        }
    }
    return 0;
}
