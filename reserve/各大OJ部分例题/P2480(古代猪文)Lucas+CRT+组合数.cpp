#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
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
#define LL long long
#define ld long double
using namespace std;
const LL N=3e5+5;
const int SIZ=1e7;
const LL inf=1e12;
template<typename T>
T invv(const T& x, const T& y) {
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
struct CRT{
    LL md,v;
    friend ostream& operator<<(ostream& ot,CRT& c){
        return ot<<c.md<<' '<<c.v;
    }
};
CRT calc_CRT(vector<CRT>& vec){
    LL a=vec[0].md,b=vec[0].v;
    for(int i=1;i<vec.size();i++){
        LL c=vec[i].md,d=vec[i].v;
        LL g=gcd(a,c);
        LL k=b%g;
        if(k!=d%g){
            return {-1,0};
        }
        a/=g;
        c/=g;
        b/=g;
        d/=g;
        LL v=b*c*invv(c,a)+d*a*invv(a,c);
        v%=a*c;
        v+=a*c;
        v%=a*c;
        b=v*g+k;
        a=a*c*g;
    }
    return {a,b};
}
struct P{
    LL v;
    int t;
};
vector<P> fact(LL v){
    vector<P> res;
    for(LL i=2;i*i<=v;i++){
        int cc=0;
        while(v%i==0)v/=i,cc++;
        if(cc)res.push_back({i,cc});
    }
    if(v)res.push_back({v,1});
    return res;
}
LL mod=999911659;
vector<LL> inz;
LL fac[N],inv[N];
LL qpow(LL a,LL t,LL md){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=md;
        a*=a,a%=md;
        t>>=1;
    }
    return res;
}
void init(LL md){
    LL tp=min(N,md);
    fac[0]=1;
    for(int i=1;i<tp;i++)fac[i]=fac[i-1]*i%md;
    inv[tp-1]=qpow(fac[tp-1],md-2,md);
    for(int i=tp-2;~i;i--)inv[i]=inv[i+1]*(i+1)%md;
}
LL C(LL m,LL n,LL md){
    if(m<n)return 0;
    return fac[m]*inv[n]%md*inv[m-n]%md;
}
LL Lucas(LL m,LL n,LL md){
    if(m<n)return 0;
    if(n==0)return 1;
    return Lucas(m/md,n/md,md)*C(m%md,n%md,md)%md;
}
signed main(){
    IOS;
    LL n,g;
    cin>>n>>g;
    if(g==999911659){
        cout<<0;
        return 0;
    }
    for(LL i=1;i*i<=n;i++){
        if(n%i==0){
            if(i*i==n)inz.push_back(i);
            else{
                inz.push_back(i);
                inz.push_back(n/i);
            }
        }
    }
    vector<CRT> eqa;
    vector<P> res=fact(mod-1);
    for(auto mdd:res){
        LL md=mdd.v;
        init(md);
        LL tot=0;
        for(LL i:inz){
            tot+=Lucas(n,i,md);
            tot%=md;
        }
        eqa.push_back({md,tot});
    }
    auto rr= calc_CRT(eqa);
    cout<<qpow(g,rr.v,mod);
}
