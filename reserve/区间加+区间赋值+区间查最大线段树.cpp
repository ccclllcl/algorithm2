#include<bits/stdc++.h>
#define ls ((u)<<1)
#define rs (((u)<<1)|1)
#define LL long long
using namespace std;
const int N=6e6;
LL inf=1e18;
LL ma[N];
LL fu[N];
LL laz[N];
LL A[N];
void pushup(int u){
    ma[u]=max(ma[ls],ma[rs]);
}
void build(int u,int l,int r){
    if(l==r){
        ma[u]=A[l];
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(u);
}
void pushdownfu(int u,int l,int r);
void pushdownadd(int u,int l,int r);
void pushdownfu(int u,int l,int r){
    if(l==r)return;
    if(fu[u] ==inf){
        return;
    }
    laz[u]=0;
    fu[ls]=fu[u];
    fu[rs]=fu[u];
    ma[ls]=ma[rs]=fu[u];
    fu[u]=inf;
}
void pushdownadd(int u,int l,int r){
    if(l==r)return;
    if(!laz[u])return;
    int mid=(l+r)>>1;
    pushdownfu(ls,l,mid);
    pushdownfu(rs,mid+1,r);
    ma[ls]+=laz[u];
    ma[rs]+=laz[u];
    laz[ls]+=laz[u];
    laz[rs]+=laz[u];
    laz[u]=0;
}
void change(int u,int l,int r,int L,int R,LL v,int op){
    if(L<=l&&R>=r){
        if(op==1){
            fu[u]=ma[u]=v;
            laz[u]=0;
        }else{
            pushdownfu(u,l,r);
            laz[u]+=v;
            ma[u]+=v;
        }
        return;
    }
    pushdownfu(u,l,r);
    pushdownadd(u,l,r);
    int mid=(l+r)>>1;
    if(L<=mid)change(ls,l,mid,L,R,v,op);
    if(R>mid)change(rs,mid+1,r,L,R,v,op);
    pushup(u);
}
LL query(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r)return ma[u];
    pushdownfu(u,l,r);
    pushdownadd(u,l,r);
    int mid=(l+r)>>1;
    LL res=-inf;
    if(L<=mid)res=max(res, query(ls,l,mid,L,R));
    if(R>mid)res=max(res, query(rs,mid+1,r,L,R));
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    LL n,q;
    cin>>n>>q;
    fill(fu,fu+n*5,inf);
    for(int i=1;i<=n;i++)cin>>A[i];
    build(1,1,n);
    for(int _=0;_<q;_++){
        int op;
        LL l,r;
        cin>>op>>l>>r;
        if(op==1||op==2){
            LL x;
            cin>>x;
            change(1,1,n,l,r,x,op);
        }else{
            cout<<query(1,1,n,l,r)<<'\n';
        }
    }
}