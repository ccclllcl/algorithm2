#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define all(x) (x).begin(),(x).end()
#define Yes(x,y) cout<<((x)?"Yes":"No")<<y
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
const int N=6e5+5;
const int SIZ=1e7;
const LL inf=1e17;
struct P{
    int x;
    LL val;
    P(int x,LL val):x(x),val(val){};
};
vector<P> G[N];
void addedge(int x,int y,LL val){
    G[x].emplace_back(y,val);
}
int n,m;
LL spfa(int s,int t){
    vector<bool> vis(n+1);
    vector<LL> dis(n+1,inf);
    queue<int> q;
    q.push(s);
    dis[s]=0;
    vis[s]=true;
    while(!q.empty()){
        int x=q.front();q.pop();
        vis[x]=false;
        for(auto [ne,val]:G[x]){
            LL nv=val+dis[x];
            if(nv<dis[ne]){
                dis[ne]=nv;
                if(!vis[ne])
                    q.push(ne),
                            vis[ne]=true;
            }
        }
    }
    return dis[t];
}
signed main(){
    IOS;
    cin>>n;
    int h;
    cin>>h;
    while(h--){
        int l,r,k;
        cin>>l>>r>>k;
        addedge(r,l-1,-k);//num[l-1]-num[r]<=-k   ->  num[r]-num[l-1]>=k
    }
    for(int i=0;i<n;i++)addedge(i,i+1,1), addedge(i+1,i,0);  //  0 <= num[i+1]-num[i] <= 1
    LL res=-spfa(n,0);
    cout<<res;
}
