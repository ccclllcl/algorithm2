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
const LL mod=998244353;
const LL inv2=(mod+1)/2;
LL Fact[NN],Inv[NN];
const LL rgt=3;
LL rgtpow[23];
using vit=vector<LL>::iterator;
LL norm(LL a){
    a%=mod;a+=mod;a%=mod;
    return a;
}
LL qpow(LL a,LL t=mod-2){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=mod;
        a*=a,a%=mod;
        t>>=1;
    }
    return res;
}
void Init(){
    Fact[0]=1;
    for(int i=1;i<NN;i++)Fact[i]=Fact[i-1]*i%mod;
    Inv[NN-1]=qpow(Fact[NN-1]);
    for(int i=NN-2;~i;i--)Inv[i]=Inv[i+1]*(i+1)%mod;
    LL d=1;
    for(int i=0;i<23;i++){
        rgtpow[i]=qpow(rgt,(mod-1)/d);
        d<<=1;
    }
}
LL Comb(LL m,LL n){
    if(m<n||n<0)return 0ll;
    return Fact[m]*Inv[n]%mod*Inv[m-n]%mod;
}
void NTT(vector<LL>& a,const int n,int op){//对a.begin(),a.begin()+n这部分作ntt,要求n为2的幂次
    assert(__builtin_popcount(n)==1);
    static vector<int> R;
    if(R.size()!=n){
        R.resize(n);
        R[0]=0;
        for(int i=1;i<n;i++)R[i]=(i&1)*(n/2)^(R[i>>1]>>1);
    }
    for(int i=0;i<n;i++)if(R[i]<i)swap(a[i],a[R[i]]);
    for(int m=2,u=1;m<=n;m<<=1,u++){
        int k=m>>1;
        LL gn=rgtpow[u];
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
        reverse(a.begin()+1,a.begin()+n);
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
    while(!a.empty()&&a.back()==0)a.pop_back();
    return a;
}
vector<LL>& operator*=(vector<LL>& a,vector<LL> b){
    if(a.empty()||b.empty()){
        a.clear();
        return a;
    }
    int sz=a.size()+b.size()-1;
    int N=1;
    while(N<sz)N<<=1;
    a.resize(N),b.resize(N);
    NTT(a,N,1),NTT(b,N,1);
    for(int i=0;i<N;i++)a[i]*=b[i],a[i]%=mod;
    NTT(a,N,-1);
    a.resize(sz);
    while(!a.empty()&&a.back()==0)a.pop_back();
    return a;
}
vector<LL> operator+(const vector<LL>& a,const vector<LL>& b){
    vector<LL> res(max(a.size(),b.size()));
    for(int i=0;i<a.size();i++)(res[i]+=a[i])%=mod;
    for(int i=0;i<b.size();i++)(res[i]+=b[i])%=mod;
    while(!res.empty()&&res.back()==0)res.pop_back();
    return res;
}
vector<LL>& operator+=(vector<LL>& a,const vector<LL>& b){
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0;i<b.size();i++)(a[i]+=b[i])%=mod;
    while(!a.empty()&&a.back()==0)a.pop_back();
    return a;
}
vector<LL> operator-(const vector<LL>& a,const vector<LL>& b){
    vector<LL> res(max(a.size(),b.size()));
    for(int i=0;i<a.size();i++)res[i]=a[i];
    for(int i=0;i<b.size();i++)(res[i]-=b[i])%=mod;
    while(!res.empty()&&res.back()==0)res.pop_back();
    for(LL& v:res)if(v<0)v+=mod;
    return res;
}
vector<LL>& operator-=(vector<LL>& a,const vector<LL>& b){
    if(a.size()<b.size())a.resize(b.size());
    for(int i=0;i<b.size();i++)(a[i]-=b[i])%=mod;
    while(!a.empty()&&a.back()==0)a.pop_back();
    for(LL& v:a)if(v<0)v+=mod;
    return a;
}
//多项式求逆
vector<LL> INV(vector<LL> a){//记a.size()为n,res满足res*a=1(mod x^n)
    static vector<LL> f(NN);
    const int N=a.size();
    assert(N>0);
    int n=1;
    while(n<N)n<<=1;
    vector<LL> res(2*n);
    a.resize(n);
    res[0]=qpow(a[0]);
    for(int t=2;t<=n;t<<=1){
        const int t2=t<<1;
        copy(a.begin(),a.begin()+t,f.begin());
        fill(f.begin()+t,f.begin()+t2,0);
        NTT(f,t2,1);
        NTT(res,t2,1);
        for(int i=0;i<t2;i++){
            res[i]*=2-f[i]*res[i]%mod;
            res[i]%=mod;
            if(res[i]<0)res[i]+=mod;
        }
        NTT(res,t2,-1);
        fill(res.begin()+t,res.begin()+t2,0);
    }
    res.resize(N);
    return res;
}
//多项式开根
vector<LL> polysqrt(vector<LL> a){//要求a[0]==1,否则涉及二次剩余求数的平方根,返回与a同大小(n)的f,满足f*f=a(mod x^n)
    if(a.empty())return {};
    assert(a[0]==1);
    const int N=a.size();
    if(N==1)return {1};
    auto a0= polysqrt(vector<LL>(a.begin(),a.begin()+(N+1)/2));
    a0.resize(N);
    int n=1;
    while(n<N*2)n<<=1;
    auto g=INV(a0);
    a0.resize(n);
    a.resize(n);
    g.resize(n);
    NTT(a,n,1);
    NTT(g,n,1);
    NTT(a0,n,1);
    for(int i=0;i<n;i++){
        a0[i]=inv2*(a0[i]+g[i]*a[i]%mod)%mod;
    }
    NTT(a0,n,-1);
    a0.resize(N);
    return a0;
}
//多项式积分
vector<LL> Integrate(vector<LL> a){//返回a的积分形式,a[0]=0,T(res)=T(a)+1
    if(a.empty())return {};
    a.emplace_back();
    for(int i=a.size()-2;~i;i--){
        a[i+1]=a[i]*qpow(i+1)%mod;
    }
    a[0]=0;
    return a;
}
//多项式求导
vector<LL> derivative(vector<LL> a){//返回a的导数形式,T(res)=T(a)-1
    if(a.size()<=1)return {};
    for(int i=0;i<a.size()-1;i++){
        a[i]=a[i+1]*(i+1)%mod;
    }
    a.pop_back();
    return a;
}
//多项式取对数
vector<LL> polyln(vector<LL> a){  //返回f(a).size()与a.size()相同,且ln(a)=f(a),例a=1+x,f(a)=x-x^2/2+x^3/3..
    assert(!a.empty()&&a[0]==1);
    auto dd= derivative(a);
    auto pp=INV(a);
    dd=dd*pp;
    dd.resize(a.size());
    dd= Integrate(dd);
    dd.resize(a.size());
    return dd;
}
//多项式exp
vector<LL> polyexp(vector<LL> a){//返回e^(a),与a次数相同的部分,例a=1+x,res=1+x+x^2/2+x^3/6+x^4/24+...
    if(a.empty()||a.size()==1&&a[0]==0)return {1};
    assert(a[0]==0);
    const int N=a.size();
    int n=1;
    while(n<N)n<<=1;
    vector<LL> res(2*n);
    a.resize(n);
    res[0]=1;
    for(int t=2;t<=n;t<<=1){
        const int t2=t<<1;
        auto exp_t=polyln(vector<LL>(res.begin(),res.begin()+t));
        exp_t.resize(t2);
        (exp_t[0]=a[0]+1-exp_t[0])%=mod;
        for(int i=1;i<t;i++)(exp_t[i]=a[i]-exp_t[i])%=mod;
        fill(exp_t.begin()+t,exp_t.begin()+t2,0);
        NTT(res,t2,1);
        NTT(exp_t,t2,1);
        for(int i=0;i<t2;i++)(res[i]*=exp_t[i])%=mod;
        NTT(res,t2,-1);
        fill(res.begin()+t,res.begin()+t2,0);
    }
    res.resize(N);
    for(LL& v:res)v=norm(v);
    return res;
}
//多项式快速幂
vector<LL> polyQpow(vector<LL> a,LL T){//返回a^T,(与a的size相同的部分),例a=1+x+0x^2+0x^3,T=3,res=1+3x+3x^2+x^3
    if(a.empty())return {};
    if(T==0)return {1};
    if(T==1)return a;
    const int N=a.size();
    pii cs{-1,-1};
    for(int i=0;i<a.size();i++){
        if(a[i]!=0){
            cs={i,a[i]};
            break;
        }
    }
    assert(cs.first!=-1);
    a.erase(a.begin(),a.begin()+cs.first);
    LL iv=qpow(cs.second);
    for(LL& v:a)(v*=iv)%=mod;
    a=polyln(a);
    for(LL& v:a)(v*=T)%=mod;
    a= polyexp(a);
    cs.first*=T;
    cs.second=qpow(cs.second,T);
    vector<LL> _tp(cs.first);
    for(LL& v:a)(v*=cs.second)%=mod;
    a.insert(a.begin(),all(_tp));
    a.resize(N);
    return a;
}
//多项式带余除法
pair<vector<LL>,vector<LL>> polyMod(vector<LL> a,vector<LL> g){//a=g*res.x+res.y(res.y的次数小于g的次数)
    while(!a.empty()&&a.back()==0)a.pop_back();
    while(!g.empty()&&g.back()==0)g.pop_back();
    const int n=a.size()-1;
    const int m=g.size()-1;
    if(n<m)return {{0},a};
    reverse(all(a));reverse(all(g));
    vector<LL> ta=vector<LL>(a.begin(),a.begin()+min(n-m+1,n+1));
    vector<LL> tg=vector<LL>(g.begin(),g.begin()+min(n-m+1,m+1));
    tg.resize(n-m+1);
    tg=INV(tg);
    ta=ta*tg;
    ta.resize(n-m+1);
    reverse(all(ta));
    reverse(all(a));reverse(all(g));
    g=g*ta;
    a-=g;
    while(!a.empty()&&a.back()==0)a.pop_back();
    return {ta,a};
}
/*
 * 给定x1,x2,x3...xn
 * 返回(x-x1)*(x-x2)*(x-x3)*...*(x-xn)
 */
vector<LL> _polyMultiply(vit first,vit end){
    assert(first<end);
    function<vector<LL>(vit,vit)> dfs=[&](vit l,vit r)->vector<LL>{
        if(l==r-1){
            LL v=-*l;
            if(v<0)v+=mod;
            return {v,1};
        }
        auto md=l+(r-l)/2;
        return dfs(l,md)*dfs(md,r);
    };
    return dfs(first,end);
}
//多项式单点求值
LL polyCalc(const vector<LL>& a,LL x){
    LL res=0;
    LL b=1;
    for(LL i : a){
        res+=b*i%mod;
        res%=mod;
        b*=x;b%=mod;
    }
    return res;
}
vector<LL> _polyMultiCalc(const vector<LL>& a,const vector<LL>& X){
    int N=X.size();
    if(N==1){
        return {polyCalc(a,X[0])};
    }
    vector<LL> res;
    vector<LL> X0(X.begin(),X.begin()+N/2);
    vector<LL> X1(X.begin()+N/2,X.end());
    auto g0= _polyMultiply(X0.begin(),X0.end());
    auto a0=polyMod(a,g0).second;
    auto _t=_polyMultiCalc(a0,X0);
    res.insert(res.end(),all(_t));
    auto g1= _polyMultiply(X1.begin(),X1.end());
    auto a1=polyMod(a,g1).second;
    _t= _polyMultiCalc(a1,X1);
    res.insert(res.end(),all(_t));
    return res;
}
//多项式快速多点求值(nlogn^2)
vector<LL> polyMultiCalc(const vector<LL>& a,const vector<LL>& X){
    assert(!X.empty());
    if(a.empty()){
        return vector<LL>(X.size());
    }
    auto res= _polyMultiCalc(a,X);
    return res;
}
//vector<LL> Brute(const vector<LL>& a,const vector<LL>& X){
//    vector<LL> res;
//    res.reserve(X.size());
//    for(LL i:X)res.emplace_back(polyCalc(a,i));
//    return res;
//}
/*
 * 返回多项式:sum(vi*[j!=i]prod(x-xj))
 */
vector<LL> _polyMultiInsert(vit v1,vit vn,vit x1,vit xn){
    if(v1==vn-1){
        return {*v1};
    }
    const int N=(vn-v1);
    auto f0= _polyMultiInsert(v1,v1+N/2,x1,x1+N/2);
    auto M0= _polyMultiply(x1,x1+N/2);
    auto f1= _polyMultiInsert(v1+N/2,v1+N,x1+N/2,x1+N);
    auto M1= _polyMultiply(x1+N/2,x1+N);
    return f0*M1+f1*M0;
}
//多项式快速插值(nlogn^2)
vector<LL> polyQuickInsert(const vector<pll>& pot){
    vector<LL> X(pot.size());
    for(int i=0;i<pot.size();i++)X[i]=pot[i].first;
    auto M= _polyMultiply(all(X));
    M= derivative(M);
    auto V= polyMultiCalc(M,X);
    for(int i=0;i<pot.size();i++){
        V[i]=qpow(V[i])*pot[i].second%mod;
    }
    return _polyMultiInsert(all(V),all(X));
}
/*
 * 计算(x+c)^T
 */
vector<LL> Comb_Poly(LL c,LL T){
    vector<LL> res(T+1);
    LL b=1;
    for(int i=0;i<=T;i++){
        res[i]=b*Comb(T,i)%mod;
        b*=c;
        b%=mod;
    }
    reverse(all(res));
    return res;
}
/*多项式平移
 * 给定f(x)和c,返回f(x+c)
 */
vector<LL> PolyMove(const vector<LL>& a,LL c){
    if(a.size()<=1)return a;
    vector<LL> A(a.size());
    vector<LL> B(a.size());
    int n=a.size()-1;
    for(int i=0;i<=n;i++)A[i]=a[n-i]*Fact[n-i]%mod;
    LL b=1;
    for(int i=0;i<=n;i++){
        B[i]=b*Inv[i]%mod;
        b*=c;b%=mod;
    }
    A=A*B;
    fill(all(B),0);
    for(int i=0;i<=n;i++){
        B[i]=Inv[i]*A[n-i]%mod;
    }
    return B;
}
signed main(){
    IOS;
    Init();
    int n,m;
    cin>>n>>m;
    vector<LL> A(n+1);
    cin>>A;
    vector<LL> X(m);
    cin>>X;
    auto res= polyMultiCalc(A,X);
    for(LL v:res)cout<<v<<'\n';
}
