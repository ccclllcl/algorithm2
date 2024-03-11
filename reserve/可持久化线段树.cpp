#include<bits/stdc++.h>
using namespace std;
typedef int LL;
#define lc ((u)<<1)
#define rc ((u)<<1|1)
const int R=1e4;
const int S=1e4;
const LL N= 1e8 + 1;
const LL M=1e6+1;
int arr[S+1];
int ls[N];
int rs[N];
int siz[N];
int num[N];
int root[M];
int cnt=0;
void change(int &u,int v,int l,int r,int p,int k){
    u=++cnt;
    ls[u]=ls[v];
    rs[u]=rs[v];
    if(l==r){
        num[u]=num[v]+k;
        if(num[u])siz[u]=1;
        else siz[u]=0;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid)change(ls[u],ls[v],l,mid,p,k);
    else change(rs[u],rs[v],mid+1,r,p,k);
    siz[u]=siz[ls[u]]+siz[rs[u]];
    if(!siz[u]){
        u=0;
        return;
    }
}
int merge(int x,int y,int l,int r){
    if(!x||!y)return x+y;
    int u=++cnt;
    if(l==r){
        num[u]=num[x]+num[y];
        if(num[u])siz[u]=1;
        else return 0;
        return u;
    }
    int mid=(l+r)>>1;
    ls[u]=merge(ls[x],ls[y],l,mid);
    rs[u]=merge(rs[x],rs[y],mid+1,r);
    siz[u]=siz[ls[u]]+siz[rs[u]];
    return u;
}
int subtr(int x,int y,int l,int r){
    if(!y)return x;
    if(l==r){
        int dis=num[x]-num[y];
        if(dis){
            int u=++cnt;
            siz[u]=1;
            return u;
        }else{
            return 0;
        }
    }
    int mid=(l+r)>>1;
    int tls= subtr(ls[x],ls[y],l,mid);
    int trs= subtr(rs[x],rs[y],mid+1,r);
    int tsz=siz[tls]+siz[trs];
    if(tsz){
        return 0;
    }
    int u=++cnt;
    siz[cnt]=tsz;
    ls[u]=tls;
    rs[u]=trs;
    return u;
}
void CH(int u,int l,int r,int p,int v,int k){
    change(root[u],root[u],0,R,v,k);
    if(l==r)return;
    int mid=(l+r)>>1;
    if(p<=mid)CH(lc,l,mid,p,v,k);
    else CH(rc,mid+1,r,p,v,k);
}
int query(int u,int l,int r,int ll,int rr){
    if(ll<=l&&rr>=r){
        return root[u];
    }
    int mid=(l+r)>>1;
    int res=0;
    if(ll<=mid)res=query(lc,l,mid,ll,rr);
    if(rr>mid)res=merge(res, query(rc,mid+1,r,ll,rr),0,S);
    return res;
}
void xCH(int p,int v){
    CH(1,0,S,p,arr[p],-1);
    arr[p]=v;
    CH(1,0,S,p,v,1);
}
int Xq(int ll,int rr){
    int res=query(1,0,S,ll,rr);
    return siz[res];
}
void init(){
    for(int i=0;i<S;i++)CH(1,0,S,i,0,1);
}
int main(){
    init();
    xCH(5,3);
    xCH(6,4);
    xCH(4,3);
    cout<<Xq(0,10);
}