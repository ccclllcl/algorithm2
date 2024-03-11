#include<bits/stdc++.h>
#define LL long long
#define ls ((u)<<1)
#define rs ((u)<<1|1)
const int inf=1e9;
using namespace std;
const int N=1e6+5;
int mi[N],tag[N];
void cov(int u,int v){
    mi[u]+=v;
    tag[u]+=v;
}
void up(int u){
    mi[u]=min(mi[ls],mi[rs]);
}
void down(int u){
    if(tag[u]){
        cov(ls,tag[u]);
        cov(rs,tag[u]);
        tag[u]=0;
    }
}
void change(int u,int l,int r,int L,int R,int v){
    if(L>R)return;
    if(L<=l&&R>=r){
        cov(u,v);
        return;
    }
    down(u);
    int mid=(l+r)>>1;
    if(L<=mid)change(ls,l,mid,L,R,v);
    if(R>mid)change(rs,mid+1,r,L,R,v);
    up(u);
}
int query(int u,int l,int r,int L,int R){
    if(L>R)return inf;
    if(L<=l&&R>=r)return mi[u];
    down(u);
    int mid=(l+r)>>1;
    int res=inf;
    if(L<=mid)res=min(res, query(ls,l,mid,L,R));
    if(R>mid)res=min(res, query(rs,mid+1,r,L,R));
    return res;
}
int n;
int A[N];
void solve(){
    cin>>n;
    for(int i=1;i<=4*n;i++)mi[i]=tag[i]=0;
    for(int i=1;i<=n;i++)cin>>A[i];
    unordered_map<int,int> la,lla;
    for(int i=1;i<=n;i++){
        int v=A[i];
        change(1,1,n,lla[v]+1,la[v],-1);
        change(1,1,n,la[v]+1,i,1);
        if(query(1,1,n,1,i)==0){
            cout<<"boring\n";
            return;
        }
        lla[v]=la[v];
        la[v]=i;
    }
    cout<<"non-boring\n";
}
signed main(){
    auto start = std::chrono::steady_clock::now();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int _;
    cin>>_;
    while(_--)solve();

    auto end = std::chrono::steady_clock::now();

    // 计算程序段用时
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "程序段用时：" << duration.count()/1000 << " 毫秒" << std::endl;
}