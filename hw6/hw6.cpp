#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <stack>

using namespace std;
const double inf = 10000000.0;
double dp[1005][1005];
double p[1005];
double q[1005];
int position[1005][1005];

int m,n;
void init(){
    for(int h=0;h<1005;h++){
        for(int i=0;i<1005;i++){
            dp[h][i] = inf;
            position[h][i]=0;
        }
    }
    position[1][1] = 2;
    return;
}

void solve(){
    dp[1][1] = abs(p[1]-q[1]);
    for(int i=2;i<=m;i++){
        for(int j=n;j>=1;j--){
            dp[i][j] = abs(p[i]-q[j]) + min(dp[i-1][j],dp[i-1][j-1]);
            if(dp[i-1][j]<dp[i-1][j-1]) position[i][j] = 1;
            else position[i][j]=2;
        }
    }
    double mini = inf;
    int posi = -1;
    for(int g=1;g<=n;g++){
        if(dp[m][g]<mini){
            mini = dp[m][g];
            posi = g;
        }
    }
    stack <int> ans;
    for(int t=m;t>=1;t--){
        if(position[t][posi]==2){
            posi--;
            ans.push(t-1);
        }
    }
    cout<<mini<<endl;
    bool flag = false;
    while(!ans.empty()){
        if(flag) cout<<" ";
        flag = true;
        cout<<ans.top();
        ans.pop();
    }
    cout<<endl;
    return;

}
int main(){
    init();
    cin>>m;
    for(int g=1;g<=m;g++) cin>>p[g];
    cin>>n;
    for(int g=1;g<=n;g++) cin>>q[g];
    solve();
    return 0;





}
