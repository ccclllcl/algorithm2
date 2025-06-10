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
constexpr int N=1e6+5;
const int SIZ=1e7;
int n;
vector<int> G[N];
int A[N];
int cnt[N],tot[N];
int siz[N];
LL ans1[N],ans2[N];
int nos[N],enos[N];
constexpr LL inf=1e12;
void dfs(int x, int f){
    int c=A[x],k=cnt[c];
    int ff=0,pos=0;
    siz[x]=1;
    for(int ne:G[x]){
        if(ne==f)continue;
        int la=cnt[c];
        dfs(ne,x);
        ans1[x]+=(LL)siz[x]*siz[ne];
        siz[x]+=siz[ne];
        if(la!=cnt[c])ff++,pos=ne;
    }
    ans1[x]+=(LL)siz[x]*(n-siz[x]);
    if(k||cnt[c]!=tot[c]-1)ff++;
    cnt[c]++;
    if(ff==1){
        if(!enos[c])nos[c]=x;
        else if(enos[c]==1){
            int p=pos?n-siz[pos]:siz[x];
            ans2[c]=(LL)siz[nos[c]]*p;
        }
        enos[c]++;
    }
}
signed main(){
    IOS;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>A[i],tot[A[i]]++,nos[A[i]]=i;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        if(tot[i]==0)cout<<((LL)n)*(n-1)/2<<'\n';
        else if(tot[i]==1)cout<<ans1[nos[i]]<<'\n';
        else if(enos[i]==2){
            cout<<ans2[i]<<'\n';
        }else cout<<0<<'\n';
    }
}
