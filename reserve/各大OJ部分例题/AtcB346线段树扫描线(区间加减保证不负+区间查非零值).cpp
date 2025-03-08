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
constexpr int N=9e5+5;
const int SIZ=1e7;
constexpr LL inf=1e12;
struct P{
    LL mn,cur;
};
P info[N];
P operator+(const P& a,const P& b){
    P res;
    if(a.mn<b.mn)return a;
    if(a.mn>b.mn)return b;
    res.mn=a.mn;
    res.cur=a.cur+b.cur;
    return res;
}
LL laz[N];
void build(int u,int l,int r){
    info[u]={0,r-l+1};
    if(l==r)return;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
void cov(int u,LL v){
    info[u].mn+=v;
    laz[u]+=v;
}
void down(int u){
    if(laz[u]){
        cov(ls,laz[u]);
        cov(rs,laz[u]);
        laz[u]=0;
    }
}
void change(int u,int l,int r,int L,int R,LL v){
    if(L>R)return;
    if(L<=l&&R>=r){
        cov(u,v);
        return;
    }
    down(u);
    if(L<=mid)change(ls,l,mid,L,R,v);
    if(R>mid)change(rs,mid+1,r,L,R,v);
    info[u]=info[ls]+info[rs];
}
P query(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r){
        return info[u];
    }
    down(u);
    if(R<=mid)return query(ls,l,mid,L,R);
    if(L>mid)return query(rs,mid+1,r,L,R);
    return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
}
signed main(){
    IOS;
    int n;
    cin>>n;
    vector<int> A(n+1);
    for(itn i=1;i<=n;i++)cin>>A[i];
    vector<int> pre(n+1);
    vector<int> ppre(n+1);
    LL ans=0;
    build(1,1,n);
    for(int i=1;i<=n;i++){
        change(1,1,n,ppre[A[i]]+1,pre[A[i]],-1);
        change(1,1,n,pre[A[i]]+1,i,1);
        P res= query(1,1,n,1,i);
        if(res.mn==0)ans+=i-res.cur;
        else ans+=i;
        ppre[A[i]]=pre[A[i]];
        pre[A[i]]=i;
    }
    cout<<ans;
}
