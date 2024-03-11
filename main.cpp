#include<bits/stdc++.h>
#define LL long long
const LL inf=1e9;
using namespace std;
const int N=2e5+5;
LL mod=998244353;
LL n;
string intToBinary(int n){
    string s;
    while(n){
        if(n&1)s.push_back('1');
        else s.push_back('0');
        n>>=1;
    }
    reverse(s.begin(),s.end());
    return s;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    LL v=1e5;
    auto s=intToBinary(v);
    cout<<s<<'\n';
    cout<<s.size()<<'\n';
}