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
LL check(LL v){
    vector<int> res;
    while(v){
        res.push_back(v%10);v/=10;
    }
    int h=res.size();
    for(int i=0;i<h/2;i++){
        if(res[i]!=res[h-1-i])return false;
    }
    return true;
}
LL find(LL n){
    LL l=1,r=1e6+1;
    while(l<r){
        LL m=(l+r+1)>>1;
        if(m*m*m<=n)l=m;
        else r=m-1;
    }
    return l;
}
vector<string> arr;
LL diss(int p,int q){
    string T=arr[p]+arr[q];
    vector<int> Next;  //回溯指针  j和Next[j]之间的关系是j前面有若干个字符组成的串与[0,Next[j]-1]相同
    Next.push_back(-1);
    for(int i = 0, j = -1; i < T.size();){
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            Next.push_back(j);
        }
        else j = Next[j];  //向前减少字符匹配量
    }
    return Next[T.size()];
}
signed main(){
    IOS;
    arr={"abaac","cabaa"};
    LL v=diss(0,1);
    cout<<v;
}
