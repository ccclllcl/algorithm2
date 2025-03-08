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
const int N=2e5+5;
const int SIZ=1e7;
const LL inf=1e17;
/*计算积性函数f前缀和(记作F(n)),n~O(1e10)
定义一个整数n的ef集合为{x|存在1<=k<=n,使得n/k=x},这个集合大小~O(n^1/2)
Min_25筛流程:
 lpf(n)为 n 的素因子分解中最小的质因子,特别地lpf(1)=1
 符号:Fprime(n)=sum of (2<=i<=n and i is prime) f(i)
 Fk(n)= sum of (2<=i<=n and lpf(i)>=pk) f(i) 即由>=pk的素数组成的i的f值之和
 答案F(n)即为 F1(n)+f(1) = F1(n)+1
 Fk(n)=Fprime(n)-Fprime(pk-1) + sigma(i>=k and pi^2<=n) sigma(c>=1,pi^c+1<=n) (f(pi^c)Fi+1(n/pi^c)+f(pi^c+1))
 现在只需考虑计算Fprime即可递推得到Fk(n) (上述递推过程无需记忆化存储)
 由于递推式中只用到了集合ef(n)中的数的Fprime值,故只需计算这些数的Fprime
 将正整数n拆成若干段,每一段上的数(x),满足n/x均相同,最终会拆成|ef(n)|段,且每段的右端点均属于ef(n)    (整除分块的原理)
 将每一段用cnt编号,从 "右" 往 "左" 编,得到了段编号与段右端点的一一映射
 数组lis用来存映射  lis[编号]=右端点 (注意lis是递减的)
 数组le,ge用来存反向映射  结合id宏,id(右端点)=编号
 要求f(p) (p是素数),必须为关于p的多项式,目的是将其拆成若干完全积性函数之和
 例如f(p)=a*p^2+b*p+c,可令g0(p)=1,f1(p)=p,g2(p)=p^2(三者都为完全积性函数),则f(p)=a*g2(p)+b*g1(p)+c*g0(p)
 再令G0(n)=sum of (2<=p<=n and p is prime) g0(p)
    G1(n)=sum of (2<=p<=n and p is prime) g1(p)
    G2(n)=sum of (2<=p<=n and p is prime) g2(p)
 则Fprime(n)=a*G2(n)+b*G1(n)+c*G0(n)
接下来分别计算G0,G1,G2,采用类似埃氏筛的思路
 令Gk(n)表示sum of (2<=i<=n and (i is prime or lpf(i) > pk ) ) g(i)
 实际编程中采用单数组自身多轮dp更新的方式节约空间
 循环k轮
 一开始计算G0(n)的值,即为sum of (2<=i<=n) g(i) ,注意只需计算并存储|ef(n)|个值 G0(i)=sum of (2<=t<=lis[i]) g(t)
 之后循环更新计算k=1,2,...pcnt(pcnt为线性筛筛至n^1/2时的素数个数)时的数组
 每轮减掉会被pk筛掉的数字(即pk的倍数,pk*pk,pk*pk+1,pk*pk+2,pk*pk*pk...)的g值之和
 做法是G(n)-=g(pk)*上一轮的(G(n/pk)-G(pk-1)) (其中G(n/pk)-G(pk-1)即为g(pk),g(pk+1),g(pk+2),g(pk*pk)...的和) (上一轮已经把pk-1的倍数筛掉了)
 根据g(幂函数)的完全积性,g(pk)*g(pk)=g(pk*pk),g(pk)*g(pk+1)=g(pk*pk+1)...即可将pk的倍数,(pk*pk,pk*pk+1,pk*pk+2,pk*pk*pk...)的g值之和筛掉
 k轮之后的G数组即为所求的G0,G1,G2(只累加了p为素数时候的值),Fprime(n)=a*G2(n)+b*G1(n)+c*G0(n) 计算出|ef(n)|个点的Fprime值
 再根据递推式即可得到F1(n)
 最终得到F(n) ( = F1(n) + 1 )
*/
LL nn;
LL G[N][2];
LL pri[N],pcnt;
LL lim;
LL lis[N],le[N],ge[N];
LL sp1[N],sp2[N];
LL mod=1e9+7;
LL inv2,inv6;
LL qpow(LL a,LL t){LL res=1;while(t){if(t&1)res*=a,res%=mod;a*=a,a%=mod,t>>=1;}return res;}
LL s2(LL n){n%=mod;return n*(n+1)%mod*(2*n+1)%mod*inv6%mod;}
bool has[N];
#define id(x) (x<=lim?le[x]:ge[nn/x])
void init(){
    inv2=qpow(2,mod-2);
    inv6=qpow(6,mod-2);
    LL y;
    for(LL i=2;i<N;i++){
        if(!has[i])pri[++pcnt]=i, sp1[pcnt]= (sp1[pcnt - 1] + i) % mod, sp2[pcnt]= (sp2[pcnt - 1] + i * i % mod) % mod;
        for(int j=1;j<=pcnt&& (y= pri[j] * i) < N; j++){
            has[y]=true;
            if(i % pri[j] == 0)break;
        }
    }
}
int cnt;
void init2(){
    for(LL i=1,j;i<=nn;i=nn/j+1){
        j=nn/i;
        LL v=j%mod;
        lis[++cnt]=j;
        id(j)=cnt;
        G[cnt][0]=(v+2)*(v-1)%mod*inv2%mod;
        G[cnt][1]=s2(v)-1;
    }
}
LL Fp[N];
void Fprime(){
    for(LL k=1;k<=pcnt;k++){
        LL p=pri[k];
        LL sqp= p * p;
        for(LL i=1;lis[i]>=sqp;i++){
            LL v= lis[i] / p;
            int id=id(v);
            G[i][0]-=p*(G[id][0]-sp1[k-1])%mod;
            G[i][0]%=mod;
            G[i][1]-=p*p%mod*(G[id][1]-sp2[k-1])%mod;
            G[i][1]%=mod;
        }
    }
    for(int i=1;i<=cnt;i++)Fp[i]=(G[i][1]-G[i][0])%mod;
}
LL f_p(LL n,LL k){
    LL tp=qpow(n,k);
    return tp*(tp-1)%mod;
}
LL F(LL k,LL n){
    if(n<pri[k]||n<=1)return 0;
    int id=id(n);
    LL ans=Fp[id]-(sp2[k-1]-sp1[k-1]);
    for(LL i=k;i<=pcnt&&pri[i]*pri[i]<=n;i++){
        LL pw=pri[i],pw2=pw*pw;
        for(LL c=1;pw2<=n;c++,pw=pw2,pw2*=pri[i]){
            ans+=(f_p(pri[i],c)*F(i+1,n/pw)%mod+f_p(pri[i],c+1))%mod;
            ans%=mod;
        }
    }
    return ans;
}
signed main(){
    IOS;
    cin>>nn;
    lim=sqrt(nn);
    init();
    init2();
    Fprime();
    LL ans=F(1,nn)+1;
    ans=(ans%mod+mod)%mod;
    cout<<ans;
}
