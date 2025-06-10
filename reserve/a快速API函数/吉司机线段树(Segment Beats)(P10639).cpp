#include<bits/stdc++.h>
#include<bits/extc++.h>
#include <ext/rope>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define all(x) (x).begin(),(x).end()
#define quchong(x) (x).erase(unique(all(x)),(x).end())
#define Yes(x,y) cout<<((x)?"Yes":"No")<<y
#define yes(x,y) cout<<((x)?"yes":"no")<<y
#define YES(x,y) cout<<((x)?"YES":"NO")<<y
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
#define tll tuple<LL,LL,LL>
#define tii tuple<int,int,int>
#define plll pair<LLL,LLL>
#define ULL unsigned long long
#define LL long long
#define LLL __int128
#define ld long double
#define ui64 uint64_t
#define ui32 uint32_t
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
template<typename T>
using RBTree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
T fang(const T& a){
    return a*a;
}
template<typename T,typename Q>
bool chmax(T& u1,T& u2,const Q& v){
    if(v>u1) { u2 = u1, u1 = v;return true;}
    if(v>u2){u2=v;return true;}
    return false;
}
template<typename T,typename Q>
bool chmin(T& u1,T& u2,const Q& v){
    if(v<u1) { u2 = u1, u1 = v;return true;}
    if(v<u2){u2=v;return true;}
    return false;
}
template<typename T,typename Q>
bool chmin(T& a,const Q& b){
    return a > b && (a = b, true);
}
template<typename T,typename Q>
bool chmax(T& a,const Q& b){
    return a<b&&(a=b,true);
}
template<typename t1,typename t2>
istream& operator>>(istream& in,pair<t1,t2>& pa){
    in>>pa.first>>pa.second;
    return in;
}
template<typename t1,typename t2>
ostream& operator<<(ostream& out,const pair<t1,t2>& pa){
    out<<pa.first<<' '<<pa.second;
    return out;
}
template<typename T>
istream& operator>>(istream& in,vector<T>& arr){
    for(auto& v:arr)in>>v;
    return in;
}
template<typename T>
ostream& operator<<(ostream& out,const vector<T>& arr){
    for(auto& v:arr)out<<v<<' ';
    return out;
}
int rand(int l,int r){
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(l, r)(rng);
}
const ld eps=1e-9;
const int NN=2e6+5;
const int SIZ=1e7;
const LL inf=1e17;
int n;
LL F[NN];
struct Info{
    LL sum,mx,mx2,mn,mn2,cmx,cmn,tmx,tmn,tad;
    Info(LL v){
        sum=mx=mn=v;
        mn2=inf,mx2=-inf;
        cmx=cmn=1;
        tmn=inf,tmx=-inf,tad=0;
    }
    Info(){}
};
Info tr[NN*4];
Info operator+(Info a,Info b){
    Info res(0);
    res.sum=a.sum+b.sum;
    if(a.mx==b.mx){
        res.mx=a.mx,res.cmx=a.cmx+b.cmx,res.mx2=max(a.mx2,b.mx2);
    }else{
        if(a.mx<b.mx)swap(a,b);
        res.mx=a.mx,res.cmx=a.cmx,res.mx2=max(a.mx2,b.mx);
    }
    if(a.mn==b.mn){
        res.mn=a.mn,res.cmn=a.cmn+b.cmn,res.mn2=min(a.mn2,b.mn2);
    }else{
        if(a.mn>b.mn)swap(a,b);
        res.mn=a.mn,res.cmn=a.cmn,res.mn2=min(a.mn2,b.mn);
    }
    return res;
}
void covAdd(int u,int l,int r,LL v){
    tr[u].sum+= (r-l+1) * v;
    tr[u].mx+=v,tr[u].mn+=v;
    if(tr[u].mx2!=-inf)tr[u].mx2+=v;
    if(tr[u].mn2!=inf)tr[u].mn2+=v;
    if(tr[u].tmx!=-inf)tr[u].tmx+=v;
    if(tr[u].tmn!=inf)tr[u].tmn+=v;
    tr[u].tad+=v;
}
void covMax(int u,int l,int r,LL v){
    if(tr[u].mn>=v)return;
    tr[u].sum+=(v-tr[u].mn)*tr[u].cmn;
    if(tr[u].mx2==tr[u].mn)tr[u].mx2=v;
    if(tr[u].mx==tr[u].mn)tr[u].mx=v;
    chmax(tr[u].tmn,v);
    tr[u].mn=v,tr[u].tmx=v;
}
void covMin(int u,int l,int r,LL v){
    if(tr[u].mx <= v)return;
    tr[u].sum+=(v-tr[u].mx)*tr[u].cmx;
    if(tr[u].mn2==tr[u].mx)tr[u].mn2=v;
    if(tr[u].mn==tr[u].mx)tr[u].mn=v;
    chmin(tr[u].tmx,v);
    tr[u].mx=v,tr[u].tmn=v;
}
void pushdown(int u,int l,int r){
    if(tr[u].tad){
        covAdd(ls,l,mid,tr[u].tad);
        covAdd(rs,mid+1,r,tr[u].tad);
        tr[u].tad=0;
    }
    if(tr[u].tmx!=-inf){
        covMax(ls,l,mid,tr[u].tmx);
        covMax(rs,mid+1,r,tr[u].tmx);
        tr[u].tmx=-inf;
    }
    if(tr[u].tmn!=inf){
        covMin(ls,l,mid,tr[u].tmn);
        covMin(rs,mid+1,r,tr[u].tmn);
        tr[u].tmn=inf;
    }
}
void build(int u,int l,int r){
    tr[u].tmn=inf,tr[u].tmx=-inf,tr[u].tad=0;
    if(l==r){
        tr[u]=Info(F[l]);
        return;
    }
    build(ls,l,mid);build(rs,mid+1,r);
    tr[u]=tr[ls]+tr[rs];
}
void updateAdd(int u,int l,int r,int L,int R,LL v){
    if(L<=l&&R>=r){
        covAdd(u,l,r,v);
        return;
    }
    pushdown(u,l,r);
    if(L<=mid)updateAdd(ls,l,mid,L,R,v);
    if(R>mid)updateAdd(rs,mid+1,r,L,R,v);
    tr[u]=tr[ls]+tr[rs];
}
void updateMin(int u,int l,int r,int L,int R,LL v){
    if(tr[u].mx<=v)return;
    if(L<=l&&R>=r&&tr[u].mx2<v){
        covMin(u,l,r,v);
        return;
    }
    pushdown(u,l,r);
    if(L<=mid)updateMin(ls,l,mid,L,R,v);
    if(R>mid)updateMin(rs,mid+1,r,L,R,v);
    tr[u]=tr[ls]+tr[rs];
}
void updateMax(int u,int l,int r,int L,int R,LL v){
    if(tr[u].mn>=v)return;
    if(L<=l&&R>=r&&tr[u].mn2>v){
        covMax(u,l,r,v);
        return;
    }
    pushdown(u,l,r);
    if(L<=mid)updateMax(ls,l,mid,L,R,v);
    if(R>mid)updateMax(rs,mid+1,r,L,R,v);
    tr[u]=tr[ls]+tr[rs];
}
LL querySum(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r)return tr[u].sum;
    pushdown(u,l,r);
    LL res=0;
    if(L<=mid)res+=querySum(ls,l,mid,L,R);
    if(R>mid)res+=querySum(rs,mid+1,r,L,R);
    return res;
}
LL queryMax(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r)return tr[u].mx;
    pushdown(u,l,r);
    LL res=-inf;
    if(L<=mid)chmax(res,queryMax(ls,l,mid,L,R));
    if(R>mid)chmax(res,queryMax(rs,mid+1,r,L,R));
    return res;
}
LL queryMin(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r)return tr[u].mn;
    pushdown(u,l,r);
    LL res=inf;
    if(L<=mid)chmin(res,queryMin(ls,l,mid,L,R));
    if(R>mid)chmin(res,queryMin(rs,mid+1,r,L,R));
    return res;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>F[i];
    build(1,1,n);
    int q;
    cin>>q;
    while(q--){
        int op,l,r;LL c,ans;
        cin>>op>>l>>r;
        if(op<=3)cin>>c;
        if(op==1)updateAdd(1,1,n,l,r,c);
        if(op==2)updateMax(1,1,n,l,r,c);
        if(op==3)updateMin(1,1,n,l,r,c);
        if(op==4)ans=querySum(1,1,n,l,r);
        if(op==5)ans=queryMax(1,1,n,l,r);
        if(op==6)ans=queryMin(1,1,n,l,r);
        if(op>3)cout<<ans<<'\n';
    }
}
signed main(){
    IOS;
    int _=1;
    while(_--)solve();
}
