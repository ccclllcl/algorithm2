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
#define tll tuple<LL,LL,LL>
#define tii tuple<int,int,int>
#define LL long long
#define LLL __int128
#define ld long double
using namespace std;
template<typename T>
istream& operator>>(istream& in,vector<T>& arr){
    for(auto& v:arr)in>>v;
    return in;
}
template<typename T>
ostream& operator<<(ostream& out,vector<T>& arr){
    for(auto& v:arr)out<<v<<' ';
    return out;
}
template<typename t1,typename t2>
istream& operator>>(istream& in,pair<t1,t2>& pa){
    in>>pa.first>>pa.second;
    return in;
}
template<typename t1,typename t2>
ostream& operator<<(ostream& out,const pair<t1,t2>& pa){
    out<<pa.first<<' '<<pa.second;
    return out;
}
const int N=2e6+5;
const int SIZ=1e7;
const LL inf=1e17;
LL u[N];
bool has[N];
LL fi[N];
int cnt;
LL p[N/5];
/*
求积性函数f的前缀和sum of f(n)记作F(n),n~O(1e10),时间复杂度O(n^2/3)
注积性函数f满足f(1)=1, 若gcd(a,b)=1,则f(a*b)=f(a)*f(b),综上,f可由f(p^k)的值唯一确定
杜教筛流程:
1.寻找积性函数g满足可以快速求解g的前缀和(记作G(n))以及可以快速求解f*g的前缀和(记作S(n))
2.线性筛预处理F(n)中n<=5e6左右的部分
3.根据式子:g(1)*F(n)=S(n)-(i:2~n)g(i)*F(n/i)   第二部分用整除分块加速运算,用map"记忆化"递归计算F(n)
*/
void init(){        //预处理一部分前缀
    u[1]=1;fi[1]=1;
    LL y;
    for(LL i=2;i<N;i++){
        if(!has[i])p[cnt++]=i,u[i]=-1,fi[i]=i-1;
        for(int j=0;j<cnt&&(y=p[j]*i)<N;j++){
            has[y]=1;
            if(i%p[j]){
                u[y]=-u[i];
                fi[y]=fi[i]*(p[j]-1);
            }else{
                u[y]=0;
                fi[y]=fi[i]*p[j];
                break;
            }
        }
    }
    for(int i=2;i<N;i++)fi[i]+=fi[i-1],u[i]+=u[i-1];
}
map<LL,LL> mem_u;//记忆化
map<LL,LL> mem_fi;
LL sum_u(LL x){     //计算莫比乌斯函数前缀和
    if(x<N)return u[x];
    if(mem_u.count(x))return mem_u[x];
    LL res=1;
    for(LL i=2,j;i<=x;i=j+1){
        j=x/(x/i);
        res-=sum_u(x/i)*(j-i+1);
    }
    return mem_u[x]=res;
}
LL sum_fi(LL x){    //计算欧拉函数前缀和
    if(x<N)return fi[x];
    if(mem_fi.count(x))return mem_fi[x];
    LL res=x*(x+1)/2;
    for(LL i=2,j;i<=x;i=j+1){
        j=x/(x/i);
        res-=sum_fi(x/i)*(j-i+1);
    }
    return mem_fi[x]=res;
}
void solve(){
    LL n;
    cin>>n;
    cout<<sum_fi(n)<<' '<<sum_u(n)<<'\n';
}
signed main(){
    init();
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
