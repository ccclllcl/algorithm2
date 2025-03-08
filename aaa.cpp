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
template <typename T>
T inv(const T& x, const T& y) {
    assert(x != 0);
    T u = 0, v = 1, a = x, m = y, t;
    while (a != 0) {
        t = m / a;
        swap(a, m -= t * a);
        swap(u -= t * v, v);
    }
    u=(u%y+y)%y;
    assert(m == 1);
    return u;
}
LL mod;
LL rgt=3;
const int N=1e5;
vector<LL> MOD{998244353,1004535809};
LL qpow(LL a,LL t=mod-2){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=mod;
        a*=a,a%=mod;
        t>>=1;
    }
    return res;
}
void NTT(vector<LL>& a,int n,int op){
    static vector<int> R;
    if(R.size()!=n){
        R.resize(n);
        R[0]=0;
        for(int i=1;i<n;i++)R[i]=(i&1)*(n/2)^(R[i>>1]>>1);
    }
    for(int i=0;i<n;i++)if(R[i]<i)swap(a[i],a[R[i]]);
    for(int m=2;m<=n;m<<=1){
        int k=m>>1;
        LL gn=qpow(rgt,(mod-1)/m);
        for(int i=0;i<n;i+=m){
            LL g=1;
            for(int j=0;j<k;j++,g*=gn,g%=mod){
                LL tmp=a[i+j+k]*g%mod;
                a[i+j+k]=(a[i+j]-tmp+mod)%mod;
                a[i+j]=(a[i+j]+tmp)%mod;
            }
        }
    }
    if(op==-1){
        reverse(a.begin()+1,a.end());
        LL iv=qpow(n);
        for(int i=0;i<n;i++)a[i]*=iv,a[i]%=mod;
    }
}
vector<LL> operator*(vector<LL> a,vector<LL> b){
    if(a.empty()||b.empty())return {};
    int sz=a.size()+b.size()-1;
    int N=1;
    while(N<sz)N<<=1;
    a.resize(N),b.resize(N);
    NTT(a,N,1),NTT(b,N,1);
    for(int i=0;i<N;i++)a[i]*=b[i],a[i]%=mod;
    NTT(a,N,-1);
    a.resize(sz);
    return a;
}

void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    auto calc=[&](LL l)->LL{
        LL pre=l-k;
        LL ne=l+k;
        LL res=0;
        if(pre>0&&pre<=m)res+=m+1-pre;
        if(ne>0&&ne<=m)res+=m+1-ne;
        return res;
    };
    vector<int> dawd(n);
    cin >> dawd;
    vector<LL> A(N + 1);
    for(int i:dawd){
        A[i]++;
    }
    vector<LL> B=A;
    reverse(all(A));
    vector<LLL> ANS;
    for(LL _v:MOD){
        mod=_v;
        auto res=A*B;
        LL ans=0;
        for(int i=1;i<=N;i++){
            LL num=res[i+N];
            ans+=calc(i)*num%mod;
            ans%=mod;
        }
        ANS.emplace_back(ans);
    }
    LLL p1=MOD[0],p2=MOD[1],t1=ANS[0],t2=ANS[1];
    LLL res=p1*inv(p1,p2)*t2+p2*inv(p2,p1)*t1;
    res%=p1*p2;
    LL tt=res;
    cout<<tt;
}
signed main(){
    IOS;
    int _=1;
    while(_--)solve();
}
