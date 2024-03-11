#include<bits/stdc++.h>
#define ls ((p)<<1)
#define rs (((p)<<1)|1)
using namespace std;
typedef long long LL;
const int N=9e5+5;
const int SIZE=1e7;
int n,Q,bn;
LL b[(int)2e5+5];
vector<LL> A;
LL root[N];
LL lc[SIZE];
LL rc[SIZE];
LL sum[SIZE];
LL cnt=0;
LL merge(LL a,LL bb){
    if(!a||!bb) { return a + bb; }
    LL res=++cnt;
    lc[res]=merge(lc[a],lc[bb]);
    rc[res]=merge(rc[a],rc[bb]);
    sum[res]=sum[a]+sum[bb];
    return res;
}
void change(LL& p,LL l,LL r,LL x,LL v){
    if(!p)p=++cnt;
    sum[p]+=v;
    if(l==r){
        return;
    }
    LL mid=(l+r)>>1;
    if(x<=mid)change(lc[p],l,mid,x,v);
    else change(rc[p],mid+1,r,x,v);
}
LL query(LL p,LL l,LL r,LL L,LL R){
    if(sum[p]==0)return 0;
    if(L<=l&&R>=r)return sum[p];
    LL mid=(l+r)>>1;
    LL res=0;
    if(L<=mid)res+= query(lc[p],l,mid,L,R);
    if(R>mid)res+= query(rc[p],mid+1,r,L,R);
    return res;
}
void build(LL p,LL l,LL r){
    if(l==r){
        change(root[p],1,bn, lower_bound(b+1,b+bn+1,A[l])-b,A[l]);
        return;
    }
    LL mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    root[p]=merge(root[ls],root[rs]);
}
LL QU(LL p,LL l,LL r,LL L,LL R,LL rt){
    if(L<=l&&R>=r){
        return query(root[p],1,bn,1,rt);
    }
    LL res=0;
    LL mid=(l+r)>>1;
    if(L<=mid)res+=QU(ls,l,mid,L,R,rt);
    if(R>mid)res+=QU(rs,mid+1,r,L,R,rt);
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    A.resize(n+1);
    for(int i=1;i<=n;i++)cin>>A[i];
    cin>>Q;
    for(int i=1;i<=n;i++)b[i]=A[i];
    sort(b+1,b+1+n);
    bn= unique(b+1,b+n+1)-b-1;
    build(1,1,n);
    LL B=0;
    for(int i=0;i<Q;i++){
        LL x,y,z;
        cin>>x>>y>>z;
        x^=B;
        y^=B;
        z^=B;
        LL ans=0;
        if(z>=b[bn]){
            ans=QU(1,1,n,x,y,bn);
        }else if(z<b[1]){
            ans=0;
        }
        else{
            LL rt= upper_bound(b+1,b+1+bn,z)-b;
            ans=QU(1,1,n,x,y,rt-1);
        }
        B=ans;
        cout<<ans<<'\n';
    }
}