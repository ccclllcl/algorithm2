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
ld divi(int a,int b){
    return (ld)(a)/((ld)(b));
}
int n;
vector<vector<vector<ld>>> dp;
ld f(int i,int j,int k){
    if(i+j+k==0)return 0;
    if(dp[i][j][k]>0)return dp[i][j][k];
    if(i+j==0)return dp[i][j][k]=f(i, j+1, k-1)+divi(n,k);
    if(i+k==0)return dp[i][j][k]=f(i+1, j-1, k)+divi(n,j);
    if(k+j==0)return dp[i][j][k]=f(i-1, j, k)+divi(n,i);
    if(i==0)return dp[i][j][k]=f(i+1, j-1, k)*divi(j,(j+k))+f(i, j+1, k-1)*divi(k,(j+k))+divi(n,(j+k));
    if(j==0)return dp[i][j][k]=f(i-1, j, k)*divi(i,(i+k))+f(i, j+1, k-1)*divi(k,(i+k))+divi(n,(i+k));
    if(k==0)return dp[i][j][k]=f(i+1, j-1, k)*divi(j,(i+j))+f(i-1, j, k)*divi(i,(i+j))+divi(n,(i+j));
    return dp[i][j][k]=f(i-1, j, k)*divi(i,(i+j+k))+f(i+1, j-1, k)*divi(j,(i+j+k))+f(i, j+1, k-1)*divi(k,(i+j+k))+divi(n,(i+j+k));
};
signed main(){
    IOS;

    cin>>n;
    int c[3]={0,0,0};
    for(int i=0;i<n;i++){
        int v;
        cin>>v;
        c[v-1]++;
    }
    dp.resize(c[0]+c[1]+c[2]+1,vector<vector<ld>>(c[1]+c[2]+1,vector<ld>(c[2]+1)));
    cout<<fixed<<setprecision(12);
    cout<<f(c[0],c[1],c[2]);
}
