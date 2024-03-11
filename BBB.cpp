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
signed main(){
    IOS;
    int n;
    cin>>n;
    vector<vector<int>> mat(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>mat[i][j];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(mat[i][j])cout<<j<<' ';
        }
        cout<<'\n';
    }
}
