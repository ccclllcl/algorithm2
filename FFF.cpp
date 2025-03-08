#include<bits/stdc++.h>
#include<bits/extc++.h>
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
const int NN=4e5+5;
const int SIZ=1e7;
const LL inf=1e17;
set<int> G[NN];
int cc=0,n=0;
int fa[NN],son[NN],siz[NN],dep[NN],top[NN],dfn[NN],idfn[NN],col[NN],ff[NN];
void dfs1(int x,int f){
    dep[x]=dep[f]+1;
    col[x]=dep[x]%2;
    fa[x]=f;
    siz[x]=1;
    son[x]=0;
    if(G[x].size()>1&&col[x]==0){
        for(int ne:G[x])ff[ne]=1;
    }
    for(int ne:G[x]){
        dfs1(ne,x);
        siz[x]+=siz[ne];
        if(siz[ne]>siz[son[x]])son[x]=ne;
    }
}
void dfs2(int x,int tp){
    top[x]=tp;
    dfn[x]=++cc;
    idfn[cc]=x;
    if(son[x])dfs2(son[x],tp);
    for(int ne:G[x]){
        if(ne==son[x])continue;
        dfs2(ne,ne);
    }
}
pll tr[NN*4];
LL tag[NN*4];
pll operator+(pll a,pll b){
    if(!a.first)return b;
    if(!b.first)return a;
    return a.second<b.second?a:b;
}
void cov(int u,LL v){
    tag[u]+=v;
    tr[u].second-=v;
}
void down(int u){
    if(tag[u]){
        cov(ls,tag[u]);
        cov(rs,tag[u]);
        tag[u]=0;
    }
}
void build(int u,int l,int r){
    if(l==r){
        int x=idfn[l];
        if(ff[x]){
            tr[u]={x,siz[x]};
        }
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    tr[u]=tr[ls]+tr[rs];
}
void decrease(int u,int l,int r,int L,int R,LL v){
    if(L<=l&&R>=r){
        cov(u,v);
        return;
    }
    down(u);
    if(L<=mid)decrease(ls,l,mid,L,R,v);
    if(R>mid)decrease(rs,mid+1,r,L,R,v);
    tr[u]=tr[ls]+tr[rs];
}
void change(int u,int l,int r,int p){
    if(l==r){
        ff[idfn[l]]=0;
        tr[u]={0,0};
        return;
    }
    down(u);
    p<=mid?change(ls,l,mid,p):change(rs,mid+1,r,p);
    tr[u]=tr[ls]+tr[rs];
}
void dele(int x,LL v){
    if(x==1)return;
    G[fa[x]].erase(x);
    change(1,1,n,dfn[x]);
    if(G[fa[x]].size()==1){
        int p=*G[fa[x]].begin();
        change(1,1,n,dfn[p]);
    }
    while(x){
        decrease(1,1,n,dfn[top[x]],dfn[x],v);
        x=fa[top[x]];
    }
}
void solve(){
    cin>>n;
    G[1].insert(2);
    for(int i=2;i<=n;i++){
        int f;
        cin>>f;
        G[f+1].insert(i+1);
    }
    n++;
    dfs1(1,0);
    dfs2(1,1);
    ff[1]=1;
    build(1,1,n);
    vector<LL> D;
    for(int i=1;i<=n;i++){
        if(col[i]==0&&G[i].empty()){
            dele(i,1);
            D.emplace_back(1);
        }
    }
    while(1){
        auto [x,v]=tr[1];
        D.emplace_back(v+1);
        if(x==1)break;
        dele(x,v);
    }
    sort(all(D));
    reverse(all(D));
    int now=0;
    LL has=0;
    while(!D.empty()){
        LL v=D.back();
        D.pop_back();
        if(v==1){
            if(now==0)has++;
        }else{
            v--;
            if(now!=0){
                has+=v/2;
            }
        }
        now^=1;
    }
    LL blue=0;
    for(int i=2;i<=n;i++)if(col[i])blue++;
    LL tot=(n)/2;
    LL de=blue-(tot-has);
    cout<<de+has;
}
signed main(){
    IOS;
    int _=1;
    while(_--)solve();
}
