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
const int NN=2e5+5;
const LL inf=1e17;
int n,m,k;
vector<int> G[NN];
int col[NN];
LL siz[NN];
bool vis[NN];
LL SIZ;
int cs;
LL Res;
void DFS(int x, int f){
    siz[x]=1;
    int res=0;
    for(int ne:G[x]){
        if(ne==f||vis[ne])continue;
        DFS(ne, x);
        siz[x]+=siz[ne];
        chmax(res,siz[ne]);
    }
    chmax(res,SIZ-siz[x]);
    if(cs==-1||res<Res)Res=res,cs=x;
}
LL dp[NN];
void calc(int x,int f,int l){
    if(SIZ==1){
        if(col[x])dp[x]++;
        vis[x]=true;
        return;
    }
    cs=-1;
    DFS(x, f);
    vector<LL> dep(SIZ+1);
    auto add=[&](int x,LL v)->void{
        assert(x>0&&x<=SIZ);
        for(;x<=SIZ;x+=lowbit(x))dep[x]+=v;
    };
    auto ask=[&](int l,int r)->LL{
        chmin(r,SIZ);
        chmax(l,1);
        if(l>r)return 0ll;
        LL res=0;
        for(;r;r-=lowbit(r))res+=dep[r];
        l--;
        for(;l;l-=lowbit(l))res-=dep[l];
        return res;
    };
    function<void(int,int,int)> dfs=[&](int x,int f,int d)->void{
        if(col[x]){
            add(d,1);
        }
        for(int ne:G[x]){
            if(ne==f||vis[ne])continue;
            dfs(ne,x,d+1);
        }
    };
    function<void(int,int,int)> dfs2=[&](int x,int f,int d)->void{
        if(d>=l)return;
        dp[x]+=ask(1,l-d);
        for(int ne:G[x]){
            if(ne==f||vis[ne])continue;
            dfs2(ne,x,d+1);
        }
    };
    for(int ne:G[cs]){
        if(vis[ne])continue;
        dfs2(ne,cs,1);
        dfs(ne,cs,1);
    }
    fill(all(dep),0ll);
    reverse(all(G[cs]));
    for(int ne:G[cs]){
        if(vis[ne])continue;
        dfs2(ne,cs,1);
        dfs(ne,cs,1);
    }
    function<void(int,int,int)> shu=[&](int x,int f,int d)->void{
        if(d<=l&&col[cs])dp[x]++;
        if(d<=l&&col[x]&&x!=cs)dp[cs]++;
        for(int ne:G[x]){
            if(ne==f||vis[ne])continue;
            shu(ne,x,d+1);
        }
    };
    shu(cs,0,0);
    vis[cs]=true;
    for(int ne:G[cs]){
        if(vis[ne])continue;
        function<int(int,int)> gets=[&](int x,int f)->int{
            int res=1;
            for(int ne:G[x]){
                if(ne==f||vis[ne])continue;
                res+=gets(ne,x);
            }
            return res;
        };
        SIZ=gets(ne,cs);
        calc(ne,cs,l);
    }
}
bool check(int l){
    SIZ=n;
    for(int i=1;i<=n;i++)dp[i]=0,vis[i]=false;
    calc(1,0,l);
    for(int i=1;i<=n;i++){
        if(dp[i]<=k)return true;
    }
    return false;
}
void solve(){
    cin>>n>>m>>k;
    if(m==n&&k==0){
        cout<<0;
        return;
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    while(m--){
        int a;
        cin>>a;
        col[a]=1;
    }
    int l=0,r=n;
    //check(0);
    while(l<r){
        int md=(l+r+1)>>1;
        if(check(md))l=md;
        else r=md-1;
    }
    cout<<l+1;
}
signed main(){
    IOS;
    int _=1;
    while(_--)solve();
}
