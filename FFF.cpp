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
struct P{
    LL ma,x,t,tma;
};
P operator+(const P& a,const P& b){
    P res;
    res.ma=max(a.ma,b.ma);
    if(a.ma==b.ma){
        res.tma=a.tma+b.tma;
        if(a.x>b.x){
            res.x=a.x;
            res.t=a.t;
        }else if(a.x<b.x){
            res.x=b.x;
            res.t=b.t;
        }else {
            res.x=a.x;
            res.t=a.t+b.t;
        }
    }else if(a.ma>b.ma){
        res.tma=a.tma;
        if(a.x>b.ma){
            res.x=a.x;
            res.t=a.t;
        }else if(a.x==b.ma){
            res.x=a.x;
            res.t=a.t+b.tma;
        }else {
            res.x=b.ma;
            res.t=b.tma;
        }
    }else{
        res.tma=b.tma;
        if(a.ma>b.x){
            res.t=a.tma;
            res.x=a.ma;
        }else if(a.ma==b.x){
            res.x=a.ma;
            res.t=a.tma+b.t;
        }else{
            res.x=b.x;
            res.t=b.t;
        }
    }
    return res;
}
P Q[N*4];
LL A[N];
void build(int u,int l,int r){
    if(l==r){
        Q[u]={A[l],0,0,1};
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    Q[u]=Q[ls]+Q[rs];
}
void change(int u,int l,int r,int p,LL v){
    if(l==r){
        A[l]=v;
        Q[u]={A[l],0,0,1};
        return;
    }
    p<=mid?change(ls,l,mid,p,v):change(rs,mid+1,r,p,v);
    Q[u]=Q[ls]+Q[rs];
}
P query(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r)return Q[u];
    if(L<=mid&&R>mid)return query(ls,l,mid,L,R)+ query(rs,mid+1,r,L,R);
    if(L<=mid)return query(ls,l,mid,L,R);
    return query(rs,mid+1,r,L,R);
}
int n,q;
signed main(){
    IOS;
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>A[i];
    build(1,1,n);
    while(q--){
        int op;
        int p,l,r;
        LL x;
        cin>>op;
        if(op==1){
            cin>>p>>x;
            change(1,1,n,p,x);
        }else{
            cin>>l>>r;
            P res= query(1,1,n,l,r);
            cout<<res.t<<'\n';
        }
    }
}
