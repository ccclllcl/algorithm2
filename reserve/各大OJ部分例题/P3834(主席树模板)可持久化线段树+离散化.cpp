#include<bits/stdc++.h>
#define qwe(i,a,b) for(int i=a;i<=b;i++)
#define itn int
#define asn ans
#define reisze resize
#define mid (((l)+(r))>>1)
#define LL long long
#define int LL
using namespace std;
constexpr int N=3e5+5;
const int SIZ=2e7;
constexpr LL inf=1e12;
int cnt;
int ls[SIZ],rs[SIZ];
int sum[SIZ];
int root[N];
void change(int& u,int v,int l,int r,int p){
    u=++cnt;
    sum[u]=sum[v]+1;
    ls[u]=ls[v];
    rs[u]=rs[v];
    if(l==r)return;
    if(p<=mid)change(ls[u],ls[v],l,mid,p);
    else change(rs[u],rs[v],mid+1,r,p);
}
int query(int u,int v,int l,int r,int k){
    if(l==r)return l;
    int d=sum[ls[u]]-sum[ls[v]];
    if(d>=k)return query(ls[u],ls[v],l,mid,k);
    else return query(rs[u],rs[v],mid+1,r,k-d);
}
vector<int> B;
vector<int> A;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    A.resize(n),B.resize(n);
    for(int i=0;i<n;i++)cin>>A[i],B[i]=A[i];
    sort(B.begin(),B.end());
    int bn=B.erase(unique(B.begin(),B.end()),B.end())-B.begin();
    for(int i=1;i<=n;i++){
        int v= lower_bound(B.begin(),B.end(),A[i-1])-B.begin();
        change(root[i],root[i-1],0,bn-1,v);
    }
    for(int _=0;_<m;_++){
        int l,r,k;
        cin>>l>>r>>k;
        int v= query(root[r],root[l-1],0,bn-1,k);
        cout<<B[v]<<'\n';
    }
}
