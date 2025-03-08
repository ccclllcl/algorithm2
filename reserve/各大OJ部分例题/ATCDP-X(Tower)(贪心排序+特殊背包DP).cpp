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
const int S=2e4;
struct P{
    int w,s;
    LL v;
    bool operator<(const P& o)const{
        return w+s<o.w+o.s;
    }
};
signed main(){
    IOS;
    int n;cin>>n;
    vector<P> A(n+1);
    for(int i=1;i<=n;i++)cin>>A[i].w>>A[i].s>>A[i].v;
    sort(A.begin()+1,A.end());
    vector<vector<LL>> dp(n+1,vector<LL>(S+1));
    for(int i=1;i<=n;i++){
        for(int j=0;j<=S;j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j]);
            if(j<=A[i].s)dp[i][j+A[i].w]=max(dp[i][j+A[i].w],dp[i-1][j]+A[i].v);
        }
    }
    cout<<*max_element(dp[n].begin(),dp[n].end());
}
