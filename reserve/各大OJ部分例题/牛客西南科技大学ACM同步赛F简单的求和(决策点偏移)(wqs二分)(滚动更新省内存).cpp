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
const LL inf=1e16;
LL fang(LL x){
    return x*x;
}
signed main(){
    IOS;
    LL n,m,k;
    cin>>n>>m>>k;
    vector<LL> A(n+1);
    for(int i=1;i<=n;i++)cin>>A[i],A[i]+=i;
    LL sum=0;
    for(int i=1;i<=n;i++)sum+=A[i];
    sum*=2*k;
    sum+=m*k*k;
    vector<LL> tot(n+1);
    for(int i=1;i<=n;i++)tot[i]=tot[i-1]+A[i];
    vector<vector<LL>> dp(n+1,vector<LL>(2,inf));
    vector<vector<LL>> cs(n+1,vector<LL>(2));
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++)dp[i][0]=dp[i][1],dp[i][1]=inf,cs[i][0]=cs[i][1],cs[i][1]=0;
        for(int i=j;i<=n;i++){
            if(j==1){
                cs[i][1]=1;
                dp[i][1]=tot[i]*tot[i];
                continue;
            }
            for(int cc=cs[i][0]; cc <= i; cc++){
                LL v= dp[cc - 1][0] + fang(tot[i] - tot[cc - 1]);
                if(v<dp[i][1]){
                    dp[i][1]=v;
                    cs[i][1]=cc;
                }
            }
        }
    }
    cout<<dp[n][1]+sum;
}
