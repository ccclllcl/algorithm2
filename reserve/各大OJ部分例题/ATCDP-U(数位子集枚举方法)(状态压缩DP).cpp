#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pdd pair<double,double>
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
#define ld long double
using namespace std;
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e17;
LL dp[1<<16];
bool has[1<<16];
vector<vector<LL>> A;
int n;
#define bt(a,b) ((a>>b)&1)
LL f(LL s){
    if(has[s])return dp[s];
    has[s]=1;
    LL ans=0;
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(bt(s,i)&&(bt(s,j)))ans+=A[i][j];
    for(LL ne=s;ne>=0;ne--){
        ne&=s;
        if(ne==s||ne==0)continue;
        ans=max(ans,f(ne)+f(s^ne));
    }
    return dp[s]=ans;
}
signed main(){
    IOS;
    cin>>n;
    A.resize(n,vector<LL>(n));
    for(auto& p1:A)for(auto& p2:p1)cin>>p2;
    cout<<f((1<<n)-1);
}
