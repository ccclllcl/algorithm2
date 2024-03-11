#include<bits/stdc++.h>
#define int long long
#define ls ((u)<<1)
#define rs (((u)<<1)|1)
using namespace std;
const int N=5e5;
struct node{
    int l,r,sum,laz;
}T[N];
void pushup(int u){
    T[u].sum=T[ls].sum+T[rs].sum;
}
void pushdown(int u){
    T[ls].laz+=T[u].laz;
    T[rs].laz+=T[u].laz;
    T[ls].sum+=T[u].laz*(T[ls].r-T[ls].l+1);
    T[rs].sum+=T[u].laz*(T[rs].r-T[rs].l+1);
    T[u].laz=0;
}
void change(int l,int r,int a,int u=1){
    if(l<=T[u].l&&r>=T[u].r) { T[u].sum += a*(T[u].r-T[u].l+1), T[u].laz += a;
        return; }
    pushdown(u);
    int m=(T[u].l+T[u].r)>>1;
    if(l<=m)change(l,r,a,ls);
    if(r>m)change(l,r,a,rs);
    pushup(u);
}
int A[N];
void build(int u,int l,int r){
    T[u].l=l,T[u].r=r;
    if(T[u].l == T[u].r){
        T[u].sum=A[T[u].l]-(T[u].l>0?A[T[u].l-1]:0);
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);build(rs,mid+1,r);
    pushup(u);
}
int query(int l,int r,int u=1){
    if(l<=T[u].l&&r>=T[u].r)return T[u].sum;
    pushdown(u);
    int m=(T[u].l+T[u].r)>>1;
    int res=0;
    if(l<=m)res+= query(l,r,ls);
    if(r>m)res+= query(l,r,rs);
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>A[i];
    build(1,0,n-1);
    for(int _=0;_<m;_++){
        int op;
        cin>>op;
        if(op==1){
            int l,r,k,d;
            cin>>l>>r>>k>>d;
            l--,r--;
            change(l,l,k);
            if(r+1<n)change(r+1,r+1,-k);
            if(l<r){
                change(l+1,r,d);
                if(r+1<n)change(r+1,r+1,-(r-l)*d);
            }
        }else{
            int p;
            cin>>p;
            cout<<query(0,p-1)<<'\n';
        }
    }
    return 0;
}