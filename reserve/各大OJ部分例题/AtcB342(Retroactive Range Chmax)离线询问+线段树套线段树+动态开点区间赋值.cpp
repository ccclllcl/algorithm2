#include<bits/stdc++.h>
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define qwe(i,a,b) for(int i=a;i<=b;i++)
#define LL long long
using namespace std;
constexpr int N=2e5+5;
constexpr LL inf=1e12;
const int SIZ=7e7;
int root[N*8];
int lc[SIZ],rc[SIZ];
LL tag[SIZ];
struct P{
    int l,r;
    LL v;
};
int cnt=0;
int n,q;
void ch(int& u,int l,int r,int L,int R,LL v){
    if(!u)u=++cnt;
    if(L<=l&&R>=r){
        tag[u]=max(tag[u],v);
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid)ch(lc[u],l,mid,L,R,v);
    if(R>mid)ch(rc[u],mid+1,r,L,R,v);
}
void change(int u,int l,int r,int L,int R,P& p){
    if(L<=l&&R>=r){
        ch(root[u],1,n,p.l,p.r,p.v);
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid)change(ls,l,mid,L,R,p);
    if(R>mid)change(rs,mid+1,r,L,R,p);
}
void qu(int u,int l,int r,int p,LL& has){
    if(!u)return;
    has=max(has,tag[u]);
    if(l==r)return;
    int mid=(l+r)>>1;
    if(p<=mid)qu(lc[u],l,mid,p,has);
    else qu(rc[u],mid+1,r,p,has);
}
void query(int u,int l,int r,int p,int p2,LL& has){
    qu(root[u],1,n,p2,has);
    if(l==r){
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid)query(ls,l,mid,p,p2,has);
    else query(rs,mid+1,r,p,p2,has);
}
LL A[N];
map<int,P> M;
struct Q{
    int id;
    int t,x;
};
vector<Q> qq;
int nq=0;
LL ans[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>A[i];
    cin>>q;
    for(int i=1;i<=q;i++){
        int op;
        cin>>op;
        if(op==1){
            int l,r;
            LL x;
            cin>>l>>r>>x;
            M[i]={l,r,x};
        }else if(op==2){
            int id;
            cin>>id;
            auto it=M.find(id);
            if(it==M.end())continue;
            change(1,1,q,it->first,i,it->second);
            M.erase(it);
        }else{
            int id;
            cin>>id;
            qq.push_back({++nq,i,id});
        }
    }
    for(auto& [k,v]:M){
        change(1,1,q,k,q,v);
    }
    for(auto& tp:qq){
        LL v=A[tp.x];
        query(1,1,q,tp.t,tp.x,v);
        ans[tp.id]=v;
    }
    for(int i=1;i<=nq;i++)cout<<ans[i]<<'\n';
}
