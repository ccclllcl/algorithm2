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
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e12;
template<typename T>
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
        LL v=b*c*inv(c,a)+d*a*inv(a,c);
        v%=a*c;
        v+=a*c;
        v%=a*c;
        b=v*g+k;
        a=a*c*g;
    }
    return {a,b};
}
signed main(){
    IOS;
    vector<CRT> vec={{2,1},{5,2},{7,3},{11,4}};
    auto res= calc_CRT(vec);
    cout<<res;
}
