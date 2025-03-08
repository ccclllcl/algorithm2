#include<bits/stdc++.h>
#define LLL __int128
using namespace std;
typedef long long LL;
LLL qpow(LLL a,LL t,LLL md){
    LLL res=1;
    while(t){
        if(t&1)res*=a,res%=md;
        t>>=1;
        a*=a;
        a%=md;
    }
    return res;
}
bool Rabin(LL n){   //判断某数是否为质数(可能将非质数误判为质数)
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    static int k=5;
    if(n==2||n==3)return true;
    if(n==1)return false;
    if(n%2==0)return false;
    LLL r=0;
    LLL d=n-1;
    while(d%2==0)d>>=1,r++;
    for(int _=0;_<k;_++){
        LL a=uniform_int_distribution<LL>(2, n - 2)(rng);
        LLL g=qpow(a, d, n);
        if(g==1|| g == n - 1)continue;
        int u=0;
        for(;u<r-1;u++){
            g*=g;
            g%=n;
            if(g==n-1)break;
        }
        if(u==r-1)return false;
    }
    return true;
}
LL Pollard_Rho(LL n){   //找到n的一个非n非1的因数(可能失败)
    static mt19937_64 sj(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<LL> u0(1,n-1);
    LL c=u0(sj);
    auto f=[&](LLL x){return ((__int128)x*x+c)%n;};
    LLL x=0,y=0,s=1;
    for(int k=1;;k<<=1,y=x,s=1){
        for(int i=1;i<=k;i++){
            x=f(x);
            s=(__int128)s*abs(x-y)%n;
            if(i%127==0){
                LL d=gcd(s,n);
                if(d>1)return d;
            }
        }
        LLL d=gcd(s,n);
        if(d>1)return d;
    }
    return n;
}
void get_factor(LLL n,vector<LL>& res){   //分解质因数
    if(n==1)return;
    if(Rabin(n)){
        res.push_back(n);
        return;
    }
    LLL x=n;
    while(x==n)x= Pollard_Rho(n);
    get_factor(x,res), get_factor(n/x,res);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<LL> tp;
    get_factor(1000,tp);
    cout<<tp.size()<<'\n';
    for(LL i:tp)cout<<i<<' ';
}