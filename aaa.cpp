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
string s;
vector<int> G[NN];
vector<vector<LL>> dp;
/*
 * 0:C
 * 1:PC
 * 2:CPC
 * 3:CCPC
 * 4:S
 * 5:CS
 * 6:CCS
 * 7:PCCS
 * */
LL ans=0;
void dfs(int x,int f){
    if(s[x]=='C')dp[x][0]=1;
    else if(s[x]=='S')dp[x][4]=1;
    LL ccs=0,c=0;
    for(int ne:G[x]){
        if(ne==f)continue;
        dfs(ne,x);
        if(s[x]=='C'){
            dp[x][2]+=dp[ne][1];
            dp[x][3]+=dp[ne][2];
            dp[x][5]+=dp[ne][4];
            dp[x][6]+=dp[ne][5];
        }else if(s[x]=='P'){
            dp[x][1]+=dp[ne][0];
            dp[x][7]+=dp[ne][6];
        }
        ans+=(s[x]=='S')*dp[ne][3];
        ans+=(s[x]=='C')*dp[ne][7];
        if(s[x]=='P'){
            ans+=ccs*dp[ne][0]+c*dp[ne][6];
            ccs+=dp[ne][6],c+=dp[ne][0];
        }
    }
    ans+=dp[x][3]*dp[x][5];
    ans+=dp[x][2]*dp[x][6];
}
void solve(){
    int n;
    cin>>n;
    dp.assign(n+1,vector<LL>(8,0));
    cin>>s;s.insert(s.begin(),0);
    for(int i=1;i<=n;i++)G[i].clear();
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    ans=0;
    dfs(1,0);
    cout<<ans<<'\n';
}
signed main(){
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
