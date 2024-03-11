#include<bits/stdc++.h>
#define qwe(i,a,b) for(int i=a;i<=b;i++)
#define pii pair<int,int>
#define LL long long
using namespace std;
constexpr int N=3e5+5;
constexpr LL inf=1e12;
struct pair_hash{
    template <class T1, class T2>
    size_t operator()(pair<T1, T2> const &pair) const{
        size_t h1 = hash<T1>()(pair.first); //用默认的 hash 处理 pair 中的第一个数据 X1
        size_t h2 = hash<T2>()(pair.second);//用默认的 hash 处理 pair 中的第二个数据 X2
        return h1 ^ h2;
    }
};
LL A[N],B[N];
unordered_set<pii,pair_hash> S;
struct P{
    int a,b;
    LL v;
    bool operator<(P o)const{
        return v>o.v;
    }
};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>A[i];
    for(int i=1;i<=n;i++)cin>>B[i];
    priority_queue<P> q;
    q.push({1,1,A[1]+B[1]});
    S.insert({1,1});
    for(int i=1;i<=n;i++){
        P res=q.top();
        q.pop();
        cout<<res.v<<' ';
        if(res.a<n&&!S.count({res.a+1,res.b}))q.push({res.a+1,res.b,A[res.a+1]+B[res.b]}),S.insert({res.a+1,res.b});
        if(res.b<n&&!S.count({res.a,res.b+1}))q.push({res.a,res.b+1,A[res.a]+B[res.b+1]}),S.insert({res.a,res.b+1});
    }
}
