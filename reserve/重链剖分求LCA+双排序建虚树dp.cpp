#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL mod=998244353;
const int N=3e5+5;
map<int,vector<int>> B;
int n;
vector<int> G[N];
int dfn[N],fa[N],son[N],top[N],dep[N],siz[N],indfn[N];
int A[N];
int cnt=0;
void dfs1(int x,int f){
    fa[x]=f;
    dep[x]=dep[f]+1;
    siz[x]=1;
    int maxx=0;
    for(int ne:G[x]){
        if(ne==f)continue;
        dfs1(ne,x);
        if(siz[ne]>maxx){
            maxx=siz[ne];
            son[x]=ne;
        }
        siz[x]+=siz[ne];
    }
}
void dfs2(int x,int tp){
    dfn[x]=++cnt;indfn[cnt]=x;
    top[x]=tp;
    if(son[x])dfs2(son[x],tp);
    for(int ne:G[x]){
        if(ne==son[x]||ne==fa[x])continue;
        dfs2(ne,ne);
    }
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]])x=fa[top[x]];
        else y=fa[top[y]];
    }
    return dep[x]>dep[y]?y:x;
}
LL ans=0;
map<int,vector<int>> H;
map<int,LL> dp;
int color;
void dfs(int x){
    LL res=1;
    LL tp=0;
    for(int ne:H[x]){
        dfs(ne);
        res*=(dp[ne]+1);
        res%=mod;
        tp+=dp[ne];
        tp%=mod;
    }
    dp[x]=res;
    if(A[x]!=color){
        dp[x]--;
        ans+=dp[x]-tp;
        ans%=mod;
    }else{
        ans+=dp[x];
        ans%=mod;
    }
}
void build(vector<int>& arr){
    sort(arr.begin(),arr.end(),[](int a,int b){
        return dfn[a]<dfn[b];
    });
    int nn=arr.size();
    for(int i=0;i<nn-1;i++)arr.push_back(LCA(arr[i],arr[i+1]));
    arr.push_back(1);
    sort(arr.begin(),arr.end(),[](int a,int b){
        return dfn[a]<dfn[b];
    });
    arr.erase(unique(arr.begin(),arr.end()),arr.end());
    H.clear();
    dp.clear();
    for(int i=0;i<arr.size()-1;i++)H[LCA(arr[i],arr[i+1])].push_back(arr[i+1]);
    dfs(1);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>A[i],B[A[i]].push_back(i);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(auto& [k,v]:B){
        color=k;
        build(v);
    }
    ans=(ans%mod+mod)%mod;
    cout<<ans<<'\n';
    //for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cout<<LCA(i,j)<<'\n';
}