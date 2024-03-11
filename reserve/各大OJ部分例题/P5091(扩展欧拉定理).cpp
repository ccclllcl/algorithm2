#include<bits/stdc++.h>
#define qwe(i,a,b) for(int i=a;i<=b;i++)
#define LL long long
using namespace std;
constexpr int N=3e5+5;
constexpr LL inf=1e12;
LL a,m;
string b;
LL qpow(LL a,LL t,LL p){
    LL res=1;
    while(t){
        if(t&1)res*=a,res%=p;
        t>>=1;
        a*=a;
        a%=p;
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>a>>m>>b;
    LL v=m;
    LL res=1;
    for(LL i=2;i*i<=v;i++){
        if(v%i==0)res*=(i-1),v/=i;
        while(v%i==0){
            v/=i;
            res*=i;
        }
    }
    if(v>1)res*=v-1;
    LL di=1;
    LL ans=0;
    for(int i=b.size()-1;~i;i--){
        int k=b[i]-'0';
        ans+=di*k;
        ans%=res;
        di*=10;
        di%=res;
    }
    if(b.size()> to_string(res).size()||stol(b)>=res){
        ans=ans%res+res;
    }
    cout<<qpow(a,ans,m);
}
