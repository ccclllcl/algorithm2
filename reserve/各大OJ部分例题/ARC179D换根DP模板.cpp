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
const LL inf=1e12;
vector<int> G[N];
int n;
int siz[N],dA[N],dp1[N],dp2[N],dB[N],ma1[N],ma2[N];
int ans;
void update(int v,int x){
    if(v>dp1[x])dp2[x]=dp1[x],dp1[x]=v;
    else if(v>dp2[x])dp2[x]=v;
}
void pushup(int v,int x){
    if(v>ma1[x])ma2[x]=ma1[x],ma1[x]=v;
    else if(v>ma2[x])ma2[x]=v;
}
void dfs1(int x, int f){
    siz[x]=1;
    for(int ne:G[x]){
        if(ne==f)continue;
        dfs1(ne, x);
        update(dp1[ne],x);
        siz[x]+=siz[ne];
        int val=min(dA[ne]+2,siz[ne]*2-dp1[ne]-1);
        dA[x]+=val;
        pushup(val-dB[ne]-1,x);
    }
    dB[x]=dA[x]-ma1[x];
    if(G[x].size()>1||(x==1&&G[x].size()>0))dp1[x]++;
    if(G[x].size()>2||(x==1&&G[x].size()>1))dp2[x]++;
}
void dfs(int x,int f){
    int val=min(dA[x]+2,siz[x]*2-dp1[x]-1);
    int da=dA[f]-val;
    int sz=siz[1]-siz[x];
    int dpp=(dp1[f]==dp1[x]+1?dp2[f]:dp1[f]);
    int outval=min(da+2,sz*2-dpp-1);
    dA[x]+=outval;
    int db=da-((ma1[f]==val-dB[x]-1)?ma2[f]:ma1[f]);
    update(dpp+1,x);
    pushup(outval-db-1,x);
    dB[x]=dA[x]-ma1[x];
    ans=min(ans,dB[x]);
    for(int ne:G[x]){
        if(ne==f)continue;
        dfs(ne,x);
    }
}
signed main(){
    IOS;
    cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1,0);
    ans=dB[1];
    for(int ne:G[1])dfs(ne,1);
    cout<<ans;
}
