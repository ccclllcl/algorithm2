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
using namespace std;
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e12;
LL mod=998244353;
LL pp[N];
LL p2[N];
LL qpow(LL a,LL t){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=mod;
        a*=a,a%=mod;
        t>>=1;
    }
    return res;
}
struct P{
    LL x;
    int id;
    bool operator<(P o)const{
        return x<o.x;
    }
};
void init(){
    pp[0]=1;
    pp[1]=qpow(2, mod - 2);
    for(int i=2;i<N;i++)pp[i]= pp[i - 1] * pp[1] % mod;
    p2[0]=1;
    for(itn i=1;i<N;i++)p2[i]=p2[i-1]*2%mod;
}
//struct L{
//public:
//    vector<LL> arr;
//    int n;
//    L(int n){
//        this->n=n;
//        arr.resize(n+1);
//    }
//    void add(int x,LL v){
//        for(;x<=n;x+=lowbit(x))arr[x]+=v;
//    }
//    LL ask(itn x){
//        LL res=0;
//        for(;x;x-=lowbit(x))res+=arr[x];
//        return res;
//    }
//};
signed main(){
    IOS;
    init();
    int n;
    cin>>n;
    LL h;
    cin>>h;
    vector<P> X(n);
    for(P& i:X)cin>>i.x;
    for(itn i=0;i<n;i++)X[i].id=i+1;
    sort(X.begin(),X.end());
    vector<vector<P>> arr;
    int iii=0;
    LL la=-h-10;
    vector<P> now;
    map<int,int> ID;
    while(iii < n){
        if(X[iii].x > la + h){
            if(!now.empty())arr.push_back(now);
            for(auto& p:now){
                ID[p.id]=arr.size()-1;
            }
            now.clear();
        }
        now.push_back(X[iii]);
        la=X[iii].x;
        iii++;
    }
    if(!now.empty())arr.push_back(now);
    for(auto& p:now){
        ID[p.id]=arr.size()-1;
    }
    vector<vector<LL>> dp;
    for(auto& A:arr){
        dp.emplace_back(A.size()+1,0);
        auto& ans=dp.back();
        map<int,int> M;
        for(auto& p:A){
            M[p.id]=1;
        }
        int cc=0;
        for(auto& [k,v]:M){
            v=++cc;
        }
        for(auto& p:A)p.id=M[p.id];
        vector<int> B(cc);
        for(itn i=0;i<cc;i++)B[i]=A[i].id;
        vector<itn> pre(cc),ne(cc);
        vector<int> stk;
        for(int i=0;i<cc;i++){
            while(!stk.empty() && stk.back() > B[i])stk.pop_back();
            stk.push_back(B[i]);
            pre[i]=stk.size();
        }
        stk.clear();
        for(itn i=cc-1;~i;i--){
            while(!stk.empty() && stk.back() > B[i])stk.pop_back();
            stk.push_back(B[i]);
            ne[i]=stk.size();
        }
        ans[B[0]]+=p2[cc-ne[0]];
        ans[B[0]]%=mod;
        ans[B[cc-1]]+=p2[cc-pre[cc-1]];
        ans[B[cc-1]]%=mod;
        for(itn i=0;i<cc-1;i++){
            ans[max(B[i],B[i+1])]+=p2[cc-pre[i]-ne[i+1]];
            ans[max(B[i],B[i+1])]%=mod;
        }
        for(int i=1;i<=cc;i++)ans[i]+=ans[i-1],ans[i]%=mod;
    }
    vector<LL> res(n+1);
    res[0]=0;
    int tot=arr.size();
    vector<bool> al(tot);
    bool hh=false;
    vector<int> has(arr.size());
    for(int i=1;i<=n;i++){
        int t=ID[i];
        if(hh){
            LL div=qpow(dp[t][has[t]],mod-2);
            if(div)res[i]=res[i-1]*div%mod*(dp[t][++has[t]])%mod;
            else{
                ++has[t];
                res[i]=1;
                for(itn j=0;j<arr.size();j++)res[i]*=dp[j][has[j]],res[i]%=mod;
            }
        }else{
            has[t]++;
            if(!al[t]&&dp[t][has[t]]) {
                al[t]=1;
                tot--;
                if(!tot){
                    hh=true;
                    LL v=1;
                    for(int k=0;k<arr.size();k++)v*=dp[k][has[k]],v%=mod;
                    res[i]=v;
                }
            }
        }
    }
    for(int i=n;i;i--){
        res[i]-=res[i-1];
        res[i]%=mod;
    }
    for(LL& i:res)i=(i%mod+mod)%mod;
    // for(LL& i:res)i*=p2[n],i%=mod;
    for(LL& i:res)i=(i%mod+mod)%mod;
    for(int i=1;i<=n;i++)cout<<res[i]<<' ';
}
