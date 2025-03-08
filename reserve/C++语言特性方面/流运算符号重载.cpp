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
istream& operator>>(istream& inn,vector<T>& arr){
    for(auto& v:arr)inn>>v;
    return inn;
}
template<typename T>
ostream& operator<<(vector<T>& arr,ostream& ot){
    for(auto& v:arr)ot<<v<<' ';
}
signed main(){
    IOS;
    int n;
    LL m;
    cin>>n>>m;
    vector<LL> A(n);
    cin>>A;
    for(int i=0;i<n;i++){
        if(A[i]>m){
            cout<<i;
            return 0;
        }
        m-=A[i];
    }
    cout<<n;
}
