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
LL calc(vector<LL> A,LL k){
    int n=A.size();
    if(n==0||k==0){
        return 0ll;
    }
    if(n==1){
        return A[0];
    }
    vector<vector<LL>> dp(n,vector<LL>(k+1,inf));
    dp[0][1]=A[0];
    dp[0][0]=0;
    dp[1][0]=0;
    dp[1][1]=min(A[0],A[1]);
    for(int i=2;i<n;i++){
        dp[i]=dp[i-1];
        LL v=A[i];
        auto& arr=dp[i-2];
        for(int j=1;j<=k;j++)chmin(dp[i][j],arr[j-1]+v);
    }
    return dp[n-1][k];
}
void solve(){
    int n,q;
    cin>>n>>q;
    map<LL,LL> M;
    for(int i=0;i<q;i++){
        LL l,r;
        cin>>l>>r;
        if(l>1)M[l-1]++;
        if(r<n)M[r]++;
    }
    LL d=0;
    while((1<<d)-1<M.size())d++;
    cout<<d<<' ';
    if(d==0){
        cout<<q;
        return;
    }
    LL cs=(1<<(d-1))-((1<<d)-1-M.size());
    vector<LL> A;
    for(auto& [a,b]:M)A.emplace_back(b);
    LL ans=calc(A,cs);
    cout<<ans*2;
}
signed main(){
    IOS;
    int _=1;
    while(_--)solve();
}
