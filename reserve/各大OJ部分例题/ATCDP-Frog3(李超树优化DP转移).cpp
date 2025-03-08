#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pdd pair<double,double>
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
#define ld long double
using namespace std;
const int N=3e6;
const int SIZ=1e7;
const LL inf=1e17;
struct line{
    LL k,b;
};
line p[N*2];
int tr[N*4];
LL Y(int id,int x){
    if(id==0)return inf;
    return p[id].k*x+p[id].b;
}
void change(int u,int l,int r,int L,int R,int id){
    if(L<=l&&R>=r){
        if(Y(id,mid)<Y(tr[u],mid))swap(id,tr[u]);
        if(Y(id,l)<Y(tr[u],l))change(ls,l,mid,L,R,id);
        if(Y(id,r)<Y(tr[u],r))change(rs,mid+1,r,L,R,id);
        return;
    }
    if(L<=mid)change(ls,l,mid,L,R,id);
    if(R>mid)change(rs,mid+1,r,L,R,id);
}
LL query(int u,int l,int r,int x){
    if(l==r)return Y(tr[u],x);
    LL t=Y(tr[u],x);
    if(x<=mid)return min(t, query(ls,l,mid,x));
    else return min(t, query(rs,mid+1,r,x));
}
const int m=1e6;
signed main(){
    IOS;
    int n;
    LL c;
    cin>>n>>c;
    vector<LL> H(n+1);
    for(itn i=1;i<=n;i++)cin>>H[i];
    LL ans=0;
    p[1]={-2*H[1],H[1]*H[1]};
    change(1,1,m,1,m,1);
    for(int i=2;i<=n;i++){
        LL v=query(1,1,m,H[i]);
        v+=H[i]*H[i]+c;
        ans=v;
        p[i]={-2*H[i],v+H[i]*H[i]};
        change(1,1,m,1,m,i);
    }
    cout<<ans;
}
