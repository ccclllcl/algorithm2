#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
using namespace std;
constexpr int N=3e5+5;
const int SIZ=1e7;
constexpr LL inf=1e14;
struct P{
    int x;
    LL v;
};
vector<P> G[N];
int n;
int k;
bool is[N];
LL dp[N][2];
void dfs(int x,int f){
    LL ma=0;
    for(auto& j:G[x]){
        int ne=j.x;
        if(ne==f)continue;
        dfs(ne,x);
        if(is[x]){
            dp[x][1]+=min(dp[ne][0],dp[ne][1]+j.v);
        }else{
            LL y=min(dp[ne][0],dp[ne][1]+j.v);
            dp[x][0]+=y;
            ma=max(ma,y-dp[ne][1]);
        }
    }
    if(!is[x])dp[x][1]=dp[x][0]-ma;
    else dp[x][0]=inf;
}
signed main(){
    IOS;
    cin>>n>>k;
    for(int i=0;i<k;i++){
        int a;
        cin>>a;
        is[a]=1;
    }
    for(itn i=0;i<n-1;i++){
        int a,b;
        LL v;
        cin>>a>>b>>v;
        G[a].push_back({b,v});
        G[b].push_back({a,v});
    }
    dfs(0,-1);
    cout<<min(dp[0][0],dp[0][1]);
}
