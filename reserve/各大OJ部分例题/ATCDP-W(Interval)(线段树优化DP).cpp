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
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e17;
int n,m;
struct P{
    int x,l;
    LL v;
    bool operator<(const P& o)const{
        return x<o.x;
    }
};
LL ma[N*4],laz[N*4];
vector<P> B[2];
void cov(int u,LL v){
    ma[u]+=v;
    laz[u]+=v;
}
void down(int u){
    if(laz[u]){
        cov(ls,laz[u]);
        cov(rs,laz[u]);
        laz[u]=0;
    }
}
void change(int u,int l,int r,int L,itn R,LL v){
    if(L<=l&&R>=r){
        cov(u,v);
        return;
    }
    down(u);
    if(L<=mid)change(ls,l,mid,L,R,v);
    if(R>mid)change(rs,mid+1,r,L,R,v);
    ma[u]=max(ma[ls],ma[rs]);
}
LL query(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r)return ma[u];
    down(u);
    if(R<=mid)return query(ls,l,mid,L,R);
    if(L>mid)return query(rs,mid+1,r,L,R);
    return max(query(ls,l,mid,L,R), query(rs,mid+1,r,L,R));
}
signed main(){
    IOS;
    cin>>n>>m;
    B[0].resize(m);B[1].resize(m);
    for(int i=0;i<m;i++){
        int l,r;
        LL v;
        cin>>l>>r>>v;
        B[0][i]={l,l-1,v};
        B[1][i]={r,l-1,-v};
    }
    for(int i=0;i<2;i++)sort(B[i].begin(),B[i].end());
    int now[2]={0,0};
    for(int i=1;i<=n;i++){
        while(now[0]<m&&B[0][now[0]].x<=i){
            change(1,0,n,0,B[0][now[0]].l,B[0][now[0]].v);
            now[0]++;
        }
        LL v= query(1,0,n,0,i-1);
        change(1,0,n,i,i,v);
        while(now[1]<m&&B[1][now[1]].x<=i){
            change(1,0,n,0,B[1][now[1]].l,B[1][now[1]].v);
            now[1]++;
        }
    }
    cout<<query(1,0,n,0,n);
}
