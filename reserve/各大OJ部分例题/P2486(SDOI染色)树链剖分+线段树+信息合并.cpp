#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define int LL
#define itn LL
#define asn ans
#define reisze resize
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
using namespace std;
constexpr int N=3e5+5;
const int SIZ=1e7;
constexpr LL inf=1e12;
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
struct P{
    int nm,lc,rc;
};
P operator+(const P& a,const P& b){
    P res;
    if(!a.nm)return b;
    if(!b.nm)return a;
    res.lc=a.lc,res.rc=b.rc;
    res.nm=a.nm+b.nm;
    if(a.rc==b.lc)res.nm--;
    return res;
}
P operator~(const P& a){
    P res;
    res.lc=a.rc;res.rc=a.lc;
    res.nm=a.nm;
    return res;
}
P Q[N*4];
int tag[N*4];
void cov(int u,int v){
    tag[u]=v;
    Q[u].lc=Q[u].rc=v;
    Q[u].nm=1;
}
void down(int u){
    if(tag[u])cov(ls,tag[u]),cov(rs,tag[u]),tag[u]=0;
}
void build(int u,int l,int r){
    if(l==r){
        Q[u]={1,A[indfn[l]],A[indfn[l]]};
        return;
    }
    build(ls,l,mid);build(rs,mid+1,r);
    Q[u]=Q[ls]+Q[rs];
}
void change(int u,int l,int r,int L,int R,int v){
    if(L>R)return;
    if(L<=l&&R>=r){
        cov(u,v);
        return;
    }
    down(u);
    if(L<=mid)change(ls,l,mid,L,R,v);
    if(R>mid)change(rs,mid+1,r,L,R,v);
    Q[u]=Q[ls]+Q[rs];
}
P query(int u,int l,int r,int L,int R){
    if(L>R)return {0,0,0};
    if(L<=l&&R>=r)return Q[u];
    down(u);
    if(L<=mid&&R>mid)return query(ls,l,mid,L,R)+ query(rs,mid+1,r,L,R);
    if(L<=mid)return query(ls,l,mid,L,R);
    return query(rs,mid+1,r,L,R);
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]])x=fa[top[x]];
        else y=fa[top[y]];
    }
    return dep[x]>dep[y]?y:x;
}
void ch(int x,int y,int v){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        change(1,1,n,dfn[top[x]],dfn[x],v);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    change(1,1,n,dfn[x],dfn[y],v);
}
int ask(int x,int y){
    P res1={0,0,0};
    P res2=res1;
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]])res1=query(1,1,n,dfn[top[x]],dfn[x])+res1,x=fa[top[x]];
        else res2=query(1,1,n,dfn[top[y]],dfn[y])+res2,y=fa[top[y]];
    }
    if(dep[x]<dep[y])res2= query(1,1,n,dfn[x],dfn[y])+res2;
    else res1= query(1,1,n,dfn[y],dfn[x])+res1;
    res1=~res1;
    return (res1+res2).nm;
}
signed main(){
    IOS;
    int q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>A[i];
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs1(1,0),dfs2(1,1);
    build(1,1,n);
    while(q--){
        char op;
        cin>>op;
        int l,r,v;
        if(op=='C'){
            cin>>l>>r>>v;
            ch(l,r,v);
        }else{
            cin>>l>>r;
            cout<<ask(l,r)<<'\n';
        }
    }
}
