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
const int NN=2e6+5;
const int SIZ=1e7;
const LL inf=1e17;
LL Euler_dis(pll a,pll b){
    return abs(a.first-b.first)+abs(a.second-b.second);
}
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
void solve(){
    int n;
    cin>>n;
    pll ed;
    cin>>ed;
    vector<LL> D(n-1);
    cin>>D;
    auto check=[&](pll st,int x)->bool{
        if(x==0)return st==pll{0,0};
        LL lp= Euler_dis({0,0},st);
        LL tot=0;
        for(int i=0;i<x;i++){
            tot+=D[i];
        }
        if(tot<lp)return false;
        if((tot+lp)%2)return false;
        for(int i=0;i<x;i++){
            if(tot-D[i]+lp<D[i])return false;
        }
        return true;
    };
    if(!check(ed,n-1)){
        cout<<-1;
        return;
    }
    vector<pll> ans;
    ans.emplace_back(ed);
    pll la=ed;
    for(int x=n-2;x;x--){
        vector<pll> dai;
        for(int u=0;u<4;u++){
            pll ne= {la.first + D[x] * dx[u],la.second+D[x]*dy[u]};
            dai.emplace_back(ne);
        }
        LL b=dai[0].second-dai[0].first;

    }
}
signed main(){
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
