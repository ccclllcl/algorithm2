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
const LL inf=1e17;
struct P{
    LL a,b;
    P(LL a,LL b):a(a),b(b){};
    bool operator<(const P& o)const{
        return a==o.a?b<o.b:a<o.a;
    }
};
LL ans;
LL res=inf;
void calc(vector<P> a,vector<P> b){
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    LL now=-inf;
    int k=0;
    LL val=0;
    for(auto& tp:a){
        while(k<b.size()&&b[k].a<=tp.a)now=max(now,b[k].b),k++;
        val=max(val,min(tp.b-tp.a+1,max(0LL,now-tp.a+1)));
    }
    res=min(res,ans-2*val);
}
signed main(){
    IOS;
    int n;
    cin>>n;
    vector<LL> A(n),B(n);
    for(LL& i:A)cin>>i;
    for(LL& i:B)cin>>i;
    LL has=0;
    for(int i=0;i<n;i++)has+=abs(A[i]-B[i]);
    ans=has;
    vector<P> a,b;
    for(int i=0;i<n;i++){
        if(A[i]==B[i])continue;
        if(A[i]>B[i]){
            a.emplace_back(B[i],A[i]-1);
        }else b.emplace_back(A[i],B[i]-1);
    }
    calc(a,b),calc(b,a);
    cout<<res;
}
