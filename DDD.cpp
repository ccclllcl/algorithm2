#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
using namespace std;
constexpr int N=3e5+5;
const int SIZ=1e7;
constexpr LL inf=1e12;
LL A[N];
signed main(){
    IOS;
    map<LL,int> M;
    int n,m;
    cin>>n>>m;
    M[0]=n;
    int ans=1;
    for(int i=0;i<m;i++){
        LL x,v;
        cin>>x>>v;
        if(A[x]==v){
            cout<<ans<<'\n';
            continue;
        }
        M[A[x]]--;
        if(M[A[x]]==0)ans--;
        A[x]+=v;
        M[A[x]]++;
        if(M[A[x]]==1)ans++;
        cout<<ans<<'\n';
    }
}
