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
constexpr LL inf=1e12;
LL C1[N],C2[N];
vector<int> G[N];
int n;
LL siz[N],gg[N];
int uu[N];
int u,v;
int root;
LL ans=0;
void add(LL* C,int x,LL val){
    x++;
    for(;x<=n+1;x+=lowbit(x))C[x]+=val;
}
LL ask(const LL* C,int x){
    x++;
    LL res=0;
    for(;x;x-=lowbit(x))res+=C[x];
    return res;
}
void dfs1(int x, int f){
    siz[x]=1,gg[x]=0;
    for(int ne:G[x]){
        if(ne==f)continue;
        dfs1(ne, x);
        siz[x]+=siz[ne];
        gg[x]=max(gg[x],siz[ne]);
    }
    if(n-siz[x]<=n/2&&gg[x]<=n/2)root=x;
}
void dfs(int x,int f){
    add(C1,siz[f],-1);
    add(C1,n-siz[x],1);
    if(x!=root){
        ans+=x*ask(C1,n-2*gg[x]);
        ans-=x*ask(C1,n-2*siz[x]-1);
        ans+=x*ask(C2,n-2*gg[x]);
        ans-=x*ask(C2,n-2*siz[x]-1);
        if(!uu[x]&&uu[f])uu[x]=1;
        if(siz[x]<=n-2*siz[uu[x]?v:u])ans+=root;
    }
    add(C2,siz[x],1);
    for(int ne:G[x]){
        if(ne==f)continue;
        dfs(ne,x);
    }
    add(C1,siz[f],1);
    add(C1,n-siz[x],-1);
    if(x!=root)ans-=x*ask(C2,n-2*gg[x]),ans+=x*ask(C2,n-2*siz[x]-1);
}
void solve(){
    cin>>n;
    ans=0;
    for(int i=1;i<=n;i++)G[i].clear();
    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        G[x].push_back(y),G[y].push_back(x);
    }
    dfs1(1,0);
    dfs1(root,0);
    u=v=0;
    for(int ne:G[root]){
        if(siz[ne]>siz[u]){
            v=u;
            u=ne;
        }else if(siz[ne]>siz[v])v=ne;
    }
    for(itn i=1;i<=n+1;i++)C1[i]=C2[i]=uu[i]=0;
    for(int i=0;i<=n;i++)add(C1,siz[i],1);
    uu[0]=0;
    uu[u]=1;
    dfs(root,0);
    cout<<ans<<'\n';
}
signed main(){
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
