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
const int N=4e6+5;
const int SIZ=1e7;
const LL inf=1e12;
vector<pll> A;
struct P{
    int g[2][2];
};
P operator*(const P& b,const P& a){
    P res;
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)res.g[i][j]=false;
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++)res.g[i][j]|=(a.g[i][k]&b.g[k][j]);
    return res;
}
P tr[N*4];
vector<LL> sum;
map<LL,vector<pii>> M;
void build(int u,int l,int r){
    if(l==r){
        tr[u].g[0][0]=(A[l].first==A[l-1].first);
        tr[u].g[0][1]=(sum[l-2]==((A[l].first-A[l-1].first)*A[l-1].second));
        tr[u].g[1][0]=(sum[l-2]==((A[l].second-A[l-1].second)*A[l-1].first));
        tr[u].g[1][1]=(A[l].second==A[l-1].second);
        M[sum[l-2]-(A[l].first-A[l-1].first)*A[l-1].second].emplace_back(l,0);
        M[sum[l-2]-(A[l].second-A[l-1].second)*A[l-1].first].emplace_back(l,1);
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    tr[u]=tr[ls]*tr[rs];
}
P query(int u,int l,int r,int L,int R){
    if(L<=l&&R>=r)return tr[u];
    if(R<=mid)return query(ls,l,mid,L,R);
    if(L>mid)return query(rs,mid+1,r,L,R);
    return query(ls,l,mid,L,R)*query(rs,mid+1,r,L,R);
}
bool ver(const P& p){
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)if(p.g[i][j])return true;
    return false;
}
void change(int u,int l,int r,pii tp){
    if(l==r){
        if(!tp.second)tr[u].g[0][1]^=1;
        else tr[u].g[1][0]^=1;
        return;
    }
    tp.first<=mid?change(ls,l,mid,tp):change(rs,mid+1,r,tp);
    tr[u]=tr[ls]*tr[rs];
}
LL has=0;
int n;
void ch(LL d){
    if(M.count(has))for(auto& tp:M[has])change(1,2,n,tp);
    has+=d;
    if(M.count(has))for(auto& tp:M[has])change(1,2,n,tp);
}
signed main(){
    IOS;
    cin>>n;
    if(n==1){
        cout<<1;
        return 0;
    }
    A.resize(n+1);
    sum.resize(n+1);
    for(int i=1;i<=n;i++)cin>>A[i].first>>A[i].second;
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+A[i].first*A[i].second;
    LL ans=1;
    build(1,2,n);
    for(int i=1;i<n;i++){
        if(!ver(query(1,2,n,i+1,i+1))){
            ans++;
            ch(A[i].first*A[i].second);
            //cout<<1<<'\n';
            continue;}
        int l=i+1,r=n;
        while(l<r){
            int m=(l+r+1)>>1;
            if(ver(query(1,2,n,i+1,m)))l=m;
            else r=m-1;
        }
        ans+=l-i+1;
        //cout<<l-i+1<<'\n';
        ch(A[i].first*A[i].second);
    }
    cout<<ans;
}