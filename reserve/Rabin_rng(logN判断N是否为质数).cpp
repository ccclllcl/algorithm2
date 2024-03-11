#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL qpow(LL a,LL t,LL mod){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=mod;
        t>>=1;
        a*=a;
        a%=mod;
    }
    return res;
}
LL k=5;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
bool Rabin(LL n){
    if(n==2||n==3)return true;
    if(n==1)return false;
    if(n%2==0)return false;
    LL r=0;
    LL d=n-1;
    while(d%2==0)d>>=1,r++;
    for(int _=0;_<k;_++){
        LL a=uniform_int_distribution<LL>(2, n - 2)(rng);
        LL g=qpow(a, d, n);
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
bool isprime(LL n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0)return false;
    }
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    LL N=1e7;
    LL M=1e9;
    vector<LL> test(N);
    for(LL &i:test)i=uniform_int_distribution<LL>(2, M)(rng);
    LL d=0;
    auto start = std::chrono::high_resolution_clock::now();
    for(LL i:test){
        if(Rabin(i)) {
            d++;
        }
    }
    auto mid = std::chrono::high_resolution_clock::now();
    for(LL i:test){
        if(isprime(i)){
            d--;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(mid - start);
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - mid);
    cout<<"Rabin用时: "<<duration1.count()<<"毫秒\n";
    cout<<"朴素用时: "<<duration2.count()<<"毫秒\n";
    cout<<d;
}