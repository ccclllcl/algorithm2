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
const int N= 2e6 + 5;
const int SIZ=1e7;
const LL inf=1e17;
vector<int> _G[N];
int dep[N],son[N],fa[N],siz[N],top[N];
void dfs1(int x, int f){
    fa[x]=f;
    dep[x]=dep[f]+1;
    siz[x]=1;
    for(int ne:_G[x]){
        if(ne==f)continue;
        dfs1(ne, x);
        siz[x]+=siz[ne];
        if(siz[ne]>siz[son[x]])son[x]=ne;
    }
}
void dfs2(int x,int tp){
    top[x]=tp;
    if(son[x])dfs2(son[x],tp);
    for(int ne:_G[x]){
        if(ne==son[x]||ne==fa[x])continue;
        dfs2(ne,ne);
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
const int N=57;
void solve(){
    int n;
    cin>>n;
    vector<pii> E;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;E.emplace_back(u,v);
        _G[u].emplace_back(v);
        _G[v].emplace_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    vector<LL> d(n-1);
    cin>>d;
    d.insert(d.begin(),0);
    vector<LL> dp(n+1,0);
    vector<int> pre(n+1,0);
    for(int b=0;b<N;b++){
        for(int i=1;i<n;i++){
            if(d[i]%2){
                pre[i+1]=pre[i]^1;
            }else pre[i+1]=pre[i];
            if(pre[i+1])dp[i+1]|=(1ll<<b);
        }
        for(int i=1;i<n;i++){
            d[i]-=pre[i]+pre[i+1]-2*pre[lca(i,i+1)];
            if(d[i]<0||d[i]%2==1){
                cout<<-1;
                return;
            }
            d[i]>>=1;
        }
    }
    vector<LL> ans;
    for(auto [l,r]:E){
        if(fa[r]==l)swap(l,r);
        ans.emplace_back(dp[l]-dp[r]);
        if(ans.back()<=0){
            cout<<-1;
            return;
        }
    }
    for(LL v:ans)cout<<v<<'\n';
}
signed main(){
    IOS;
    int _=1;
    while(_--)solve();
}
