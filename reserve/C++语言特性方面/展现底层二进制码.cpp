#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define bt32 bitset<32>
#define bt64 bitset<64>
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
template<typename T>
string tran64(T& a){
    uint64_t bits=reinterpret_cast<uint64_t&>(a);
    return bt64(bits).to_string();
}
template<typename T>
string tran32(T& a){
    uint32_t bits=reinterpret_cast<uint32_t&>(a);
    return bt32(bits).to_string();
}
signed main(){
    IOS;
    int a=1;
    cout<<tran32(a);
}
