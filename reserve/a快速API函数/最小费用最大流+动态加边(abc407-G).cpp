#include<bits/stdc++.h>
#include<bits/extc++.h>
#include <ext/rope>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define all(x) (x).begin(),(x).end()
#define quchong(x) (x).erase(unique(all(x)),(x).end())
#define Yes(x,y) cout<<((x)?"Yes":"No")<<y
#define yes(x,y) cout<<((x)?"yes":"no")<<y
#define YES(x,y) cout<<((x)?"YES":"NO")<<y
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
#define plll pair<LLL,LLL>
#define ULL unsigned long long
#define LL long long
#define LLL __int128
#define ld long double
#define ui64 uint64_t
#define ui32 uint32_t
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
template<typename T>
using RBTree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
T fang(const T& a){
    return a*a;
}
template<typename T,typename Q>
bool chmax(T& u1,T& u2,const Q& v){
    if(v>u1) { u2 = u1, u1 = v;return true;}
    if(v>u2){u2=v;return true;}
    return false;
}
template<typename T,typename Q>
bool chmin(T& u1,T& u2,const Q& v){
    if(v<u1) { u2 = u1, u1 = v;return true;}
    if(v<u2){u2=v;return true;}
    return false;
}
template<typename T,typename Q>
bool chmin(T& a,const Q& b){
    return a > b && (a = b, true);
}
template<typename T,typename Q>
bool chmax(T& a,const Q& b){
    return a<b&&(a=b,true);
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
template<typename T>
istream& operator>>(istream& in,vector<T>& arr){
    for(auto& v:arr)in>>v;
    return in;
}
template<typename T>
ostream& operator<<(ostream& out,const vector<T>& arr){
    for(auto& v:arr)out<<v<<' ';
    return out;
}
int rand(int l,int r){
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(l, r)(rng);
}
const ld eps=1e-9;
const int NN=2e6+5;
const int SIZ=1e7;
const LL inf=1e17;
struct edge{
    int v;
    LL c,w;
    int ne;
};
edge E[NN];
int idx=1;
int tot;
LL d[NN];
int h[NN],cur[NN],pre[NN],vis[NN];
LL mf[NN];
void add(int u,int v,LL c,LL w){
    E[++idx]={v,c,w,h[u]};
    h[u]=idx;
    E[++idx]={u,0,-w,h[v]};
    h[v]=idx;
}
bool spfa(int s,int t){
    fill(d,d+tot+1,inf);
    fill(mf,mf+tot+1,0);
    d[s]=0;
    queue<int> q;q.push(s);
    vis[s]=1;
    mf[s]=inf;
    while(!q.empty()){
        int u=q.front();q.pop();vis[u]=0;
        for(int i=h[u];i;i=E[i].ne){
            int v=E[i].v;
            LL c=E[i].c;
            LL w=E[i].w;
            if(d[v]>d[u]+w&&c>0){
                d[v]=d[u]+w;
                mf[v]=min(mf[u],c);
                pre[v]=i;
                if(!vis[v])vis[v]=1,q.push(v);
            }
        }
    }
    return mf[t]>0;
}
pll EK(int s,int t){
    LL flow=0,cost=0;
    while(spfa(s,t)){
        for(int v=t;v!=s;){
            int i=pre[v];
            E[i].c-=mf[t];
            E[i^1].c+=mf[t];
            v=E[i^1].v;
        }
        flow+=mf[t];
        cost+=mf[t]*d[t];
    }
    return {flow,cost};
}
const LL offset=3e12;
void solve(){
    int m,n;
    cin>>m>>n;
    vector<vector<LL>> mat(m,vector<LL>(n));
    cin>>mat;
    LL SS=0;
    int s=m*n+1,t=m*n+2;
    for(int i=0;i<m;i++)for(int j=0;j<n;j++){
            SS+=mat[i][j];
            int id=i*n+j+1;
            if((i+j)%2)add(s,id,1,0);
            else add(id,t,1,0);
            if(i+1<m){
                int nid=(i+1)*n+j+1;
                if((i+j)%2)add(id,nid,1,mat[i][j]+mat[i+1][j]+offset);
                else add(nid,id,1,mat[i][j]+mat[i+1][j]+offset);
            }
            if(j+1<n){
                int nid=i*n+j+2;
                if((i+j)%2)add(id,nid,1,mat[i][j]+mat[i][j+1]+offset);
                else add(nid,id,1,mat[i][j]+mat[i][j+1]+offset);
            }
        }
    int S=t+1;
    tot=S;
    LL ans=0;
    LL F=0,CC=0;
    while(1){
        add(S,s,1,0);
        auto [flow,cost]=EK(S,t);
        if(!flow)break;
        F+=flow;
        CC+=cost;
        chmin(ans,CC-F*offset);
    }
    ans=SS-ans;
    cout<<ans;
}
signed main(){
    IOS;
    int _=1;
    while(_--)solve();
}
