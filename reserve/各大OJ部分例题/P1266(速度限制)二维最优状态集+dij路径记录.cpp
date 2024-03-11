#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=3e5+5;
double inf=1e12;
const LL SIZ=1e6;
#define pll pair<LL,LL>
class Vec{
public:
    map<LL,LL> M;
    bool check(pll tp){
        if(M.empty())return true;
        auto p1=--M.end();
        if(tp.first<=p1->first){
            p1=M.lower_bound(tp.first);
            if(p1->second<=tp.second)return false;//如二维数据都是越大越优,此处应改为>=
        }
        return true;
    }
    void update(pll tp){
        if(M.empty()){
            M[tp.first]=tp.second;
            return;
        }
        auto p1=--M.end();
        if(tp.first<=p1->first){
            p1=M.lower_bound(tp.first);
            if(p1->second<=tp.second)return;
        }
        auto pre=p1;
        while(pre!=--M.begin()&&pre->second>=tp.second)pre--;
        M.erase(++pre,++p1);
        M[tp.first]=tp.second;
    }
};
Vec dp[N];
int n,m,t;
struct PP{
    int x;
    double l;
    LL v;
};
struct P{
    int x;
    double l;
    LL vm;
    int idx;
    bool operator<(P o)const{
        return l>o.l;
    }
};
LL pre[SIZ];
LL rec[SIZ];
int cnt=1;
vector<PP> G[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>t;
    for(int i=0;i<m;i++){
        int u,v,V;
        double l;
        cin>>u>>v>>V>>l;
        G[u].push_back({v,l,V});
    }
    priority_queue<P> q;
    q.push({0,0,70,1});
    double ans=inf;
    LL p=-1;
    while(!q.empty()){
        P tp=q.top();q.pop();
        if(tp.x==t){
            if(ans>tp.l){
                ans=tp.l;
                p=tp.idx;
            }
            continue;
        }
        if(dp[tp.x].check({tp.vm,tp.l})){
            dp[tp.x].update({tp.vm,tp.l});
        }else continue;
        for(auto& j:G[tp.x]){
            P up;
            if(j.v){
                up={j.x,tp.l+j.l/j.v,j.v,tp.x};
            }else{
                up={j.x,tp.l+j.l/tp.vm,tp.vm,tp.x};
            }
            if(up.l>=ans)continue;
            if(dp[up.x].check({up.vm,up.l})) {
                up.idx=++cnt;
                pre[cnt]=tp.idx;
                rec[cnt]=up.x;
                q.push(up); }
        }
    }
    LL x=p;
    vector<LL> ot;
    while(x){
        ot.push_back(rec[x]);
        x=pre[x];
    }
    for(int i=ot.size()-1;~i;i--)cout<<ot[i]<<' ';
}
