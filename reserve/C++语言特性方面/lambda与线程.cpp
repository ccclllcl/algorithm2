#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define pause(x) this_thread::sleep_for(chrono::seconds(x))
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
class MyFunctor {
public:
    int operator[](size_t index) const; // 不是引用返回
    int& operator[](size_t index); // 是引用返回
};

int cnt1;
int MyFunctor::operator[](size_t index) const {
    cnt1++;
    return 10;
}
int tq;
int cnt2;
int &MyFunctor::operator[](size_t index) {
    cnt2++;
    return tq;
}

signed main(){
    IOS;
    thread t1([&](){
        thread t2([&](){
            t1.join();
        });
    });
}
