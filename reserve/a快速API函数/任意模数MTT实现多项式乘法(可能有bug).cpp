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
vector<LL> MOD{998244353,1004535809,469762049};
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
    return a;
}
LLL getval(LLL p1,LLL t1,LLL p2,LLL t2){
    LLL res=p1*inv(p1,p2)*t2+p2*inv(p2,p1)*t1;
    res%=p1*p2;
    return res;
}
LL Getval(vector<LL> V,LL md){
    LLL tp=getval(MOD[0],V[0],MOD[1],V[1]);
    tp=getval(MOD[1]*(LLL)MOD[0],tp,MOD[2],V[2]);
    return tp%md;
}
vector<LL> multi(const vector<LL>& a,const vector<LL>& b,LL md){
    vector<vector<LL>> V;
    for(LL v:MOD){
        V.emplace_back();
        auto& arr=V.back();
        mod=v;
        auto res=a*b;
        for(LL val:res)arr.emplace_back(val);
    }
    vector<LL> ans;
    for(int i=0;i<V[0].size();i++){
        ans.emplace_back(Getval({V[0][i],V[1][i],V[2][i]},md));
    }
    return ans;
}
vector<LL> prob(const string& s){
    istringstream si(s);
    vector<LL> res;
    LL v;
    while(si>>v)res.emplace_back(v);
    return res;
}
void solve(){
    string s1,s2;
    getline(cin,s1);
    getline(cin,s2);
    LL md;
    cin>>md;
    auto a=prob(s1),b=prob(s2);
    auto res=multi(a,b,md);
    while(res.size()>1&&res.back()==0)res.pop_back();
    cout<<res;
}
signed main(){
    IOS;
    int _=1;
    while(_--)solve();
}
/*
示例:
 in:
 1 3 3 1
 1 1
 4

 out:
 1 0 2 0 1
 PS:1 4 6 4 1各个位置mod4的结果
*/
