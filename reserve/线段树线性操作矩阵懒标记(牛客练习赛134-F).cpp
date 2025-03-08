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
#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

// TODO: Dynamic ModInt

template<typename T>
constexpr T power(T a, u64 b) {
    T res {1};
    for (; b != 0; b /= 2, a *= a) {
        if (b % 2 == 1) {
            res *= a;
        }
    }
    return res;
}

template<u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return 1ULL * a * b % P;
}

template<u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

template<typename U, U P>
requires std::unsigned_integral<U>
struct ModIntBase {
public:
    constexpr ModIntBase() : x {0} {}

    template<typename T>
    requires std::integral<T>
    constexpr ModIntBase(T x_) : x {norm(x_ % T {P})} {}

    constexpr static U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }

    constexpr U val() const {
        return x;
    }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = norm(P - x);
        return res;
    }

    constexpr ModIntBase inv() const {
        return power(*this, P - 2);
    }

    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<P>(x, rhs.val());
        return *this;
    }

    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a) {
        return os << a.val();
    }

    friend constexpr bool operator==(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }

    friend constexpr bool operator<(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() < rhs.val();
    }

private:
    U x;
};

template<u32 P>
using ModInt = ModIntBase<u32, P>;

template<u64 P>
using ModInt64 = ModIntBase<u64, P>;

constexpr u32 P = 998244353;//或1e+7
using Z = ModInt<P>;
const ld eps=1e-9;
const int NN=2e5+5;
const int SIZ=1e7;
const LL inf=1e17;
LL n,m;
const int N=7;
Z tmp[N][N];
struct Vec{
    Z a[N]{0};
};
struct Mat{
    Z g[N][N]{0};
};
Mat E;
Mat& operator*=(Mat& b,const Mat& a){
    for(int i=0;i<N;i++)for(int j=i;j<N;j++) {
            tmp[i][j]=0;
            for (int k = i; k <= j; k++) {
                (tmp[i][j] += a.g[i][k] * b.g[k][j]);
            }
        }
    for(int i=0;i<N;i++)for(int j=i;j<N;j++)b.g[i][j]=tmp[i][j];
    return b;
}
Vec& operator*=(Vec& b, const Mat& a){
    for(int i=0;i<N;i++) {
        tmp[0][i]=0;
        for (int j = i; j < N; j++) {
            tmp[0][i]+=a.g[i][j]*b.a[j];
        }
    }
    for(int i=0;i<N;i++)b.a[i]=tmp[0][i];
    return b;
}
Mat calcA(LL x){
    Mat res;
    vector<Z> tq(6);
    tq[0]=1;
    for(int i=1;i<6;i++)tq[i]=tq[i-1]*x;
    for(int i=0;i<N;i++)res.g[i][i]=1;
    for(int i=N-2;i;i--)for(int j=N-1;j>i;j--){
            res.g[i][j]=res.g[i+1][j];
            if(j<N-1)res.g[i][j]+=res.g[i+1][j+1];
        }
    for(int i=2;i<N;i++)for(int j=1;j<=N-i;j++){
            res.g[j][i+j-1]*=tq[i-1];
        }
    return res;
}
Mat calcB(LL x){
    Mat res;
    Z now=1;
    res.g[0][0]=1;
    for(int i=N-1;i;i--){
        res.g[i][i]=now;
        now*=x;
    }
    return res;
}
Mat C;
void init(){
    for(int i=0;i<N;i++)E.g[i][i]=1;
    C=E;
    for(int i=0;i<N-1;i++)C.g[0][i]=1;
}
Mat tag[NN*4];
bool has[NN*4];
Vec tr[NN * 4];
Vec operator+(const Vec& a, const Vec& b){
    Vec res;
    for(int i=0;i<N;i++)res.a[i]=(a.a[i]+b.a[i]);
    return res;
}
void cov(int u,const Mat& op){
    has[u]=true;
    tag[u]*=op;
    tr[u]*=op;
}
void down(int u){
    if(has[u]){
        cov(ls,tag[u]);
        cov(rs,tag[u]);
        tag[u]=E;
        has[u]=false;
    }
}
Z A[NN];
void build(int u,int l,int r){
    tag[u]=E;
    has[u]=false;
    if(l==r){
        Z v=A[l];
        tr[u].a[0]=0;
        Z now=1;
        for(int i=N-1;i;i--)tr[u].a[i]=now,now*=v;
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    tr[u]=tr[ls]+tr[rs];
}
void change(int u,int l,int r,int L,int R,const Mat& p){
    if(L<=l&&R>=r){
        cov(u,p);
        return;
    }
    down(u);
    if(L<=mid)change(ls,l,mid,L,R,p);
    if(R>mid)change(rs,mid+1,r,L,R,p);
    tr[u]=tr[ls]+tr[rs];
}
vector<Z> ans;
void dfs(int u,int l,int r){
    if(l==r){
        ans.emplace_back(tr[u].a[0]);
        return;
    }
    down(u);
    dfs(ls,l,mid);
    dfs(rs,mid+1,r);
}
void solve(){
    cin>>n>>m;
    LL oy;
    for(int i=1;i<=n;i++)cin>>oy,A[i]=oy;
    build(1,1,n);
    for(int _=0;_<m;_++){
        int op;
        cin>>op;
        int l,r;
        LL x;
        cin>>l>>r>>x;
        if(op==1){
            change(1,1,n,l,r,calcA(x));
        }else{
            change(1,1,n,l,r,calcB(x));
        }
        change(1,1,n,1,n,C);
    }
    dfs(1,1,n);
    cout<<ans;
}
signed main(){
    IOS;
    init();
    int _=1;
    while(_--)solve();
}
