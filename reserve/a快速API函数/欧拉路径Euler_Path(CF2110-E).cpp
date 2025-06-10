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
void solve(){
    int n;
    cin>>n;
    map<int,int> H,L;
    vector<vector<pii>> G;
    vector<pii> E;
    while(n--){
        int a,b;
        cin>>a>>b;
        H[a]=1,L[b]=1;
        E.emplace_back(a,b);
    }
    n=0;int m=0;
    for(auto& [l,r]:H)r=++m;
    for(auto& [l,r]:L)r=m+(++n);
    G.resize(n+m+1);
    vector<int> du(n+m+1);
    vector<int> fa(n+m+1);iota(all(fa),0);
    auto find=[&](int x)->int{
        while(x!=fa[x])x=fa[x]=fa[fa[x]];
        return x;
    };
    auto merge=[&](int x,int y)->void{
        x=find(x),y=find(y);
        if(x==y)return;
        fa[x]=y;
    };
    for(auto [l,r]:E){
        l=H[l],r=L[r];
        merge(l,r);
        du[l]++,du[r]++;
        G[l].emplace_back(r,G[r].size());
        G[r].emplace_back(l,G[l].size()-1);
    }
    for(int i=1;i<=n+m;i++){
        if(find(i)!=find(1)){
            cout<<"NO\n";
            return;
        }
    }
    int s=-1;
    int cc=0;
    for(int i=1;i<=n+m;i++){
        if(du[i]&1){
            cc++;
            s=i;
            if(cc>2){
                cout<<"NO\n";
                return;
            }
        }
    }
    cout<<"YES\n";
    vector<vector<bool>> del(n + m + 1);
    for(int i=0;i<G.size();i++)del[i].resize(G[i].size());
    vector<int> ans;
    vector<int> cnt(n+m+1);
    function<void(int)> Hierholzer=[&](int x)->void{
        for(int& i=cnt[x];i<G[x].size();){
            if(!del[x][i]){
                auto [ne,id]=G[x][i];
                del[ne][id]=true;
                del[x][i]=true;
                i++;
                Hierholzer(ne);
            }else ++i;
        }
        ans.emplace_back(x);
    };
    if(s==-1)s=1;
    Hierholzer(s);
    int la=ans.back();
    ans.pop_back();
    vector<int> ANS;
    map<pii,vector<int>> M;
    for(int i=0;i<E.size();i++){
        auto [l,r]=E[i];
        l=H[l],r=L[r];
        M[{l,r}].emplace_back(i+1);
    }
    while(!ans.empty()){
        int now=ans.back();ans.pop_back();
        int x=now<=m?now:la,y=now^la^x;
        ANS.emplace_back(M[{x,y}].back());
        M[{x,y}].pop_back();
        la=now;
    }
    cout<<ANS<<'\n';
}
signed main(){
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
