#include<bits/stdc++.h>
#include<bits/extc++.h>
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
int siz[NN],ch[NN][2],val[NN],fa[NN];
int root=0,cnt=0;
int get(int x){
    return ch[fa[x]][1]==x;
}
void pushup(int x){
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}
void rotate(int x){
    int y=fa[x],z=fa[y],chk=get(x);
    ch[y][chk]=ch[x][chk^1];
    if(ch[x][chk^1])fa[ch[x][chk^1]]=y;
    ch[x][chk^1]=y;
    fa[y]=x;
    fa[x]=z;
    if(z)ch[z][y==ch[z][1]]=x;
    pushup(y);
    pushup(x);
    if(z)pushup(z);
}
void splay(int x){
    for(int f;f=fa[x],f;rotate(x)){
        if(fa[f])rotate(get(x)==get(f)?f:x);
    }
    root=x;
}
void insert(int x,int v){
    if(!cnt){
        cnt=1;
        root=1;
        siz[1]=1;
        val[1]=v;
        return;
    }
    int cur=root;
    while(1){
        siz[cur]++;
        int chk=x>siz[ch[cur][0]]?(x-=siz[ch[cur][0]]+1,1):0;
        if(!ch[cur][chk]){
            ch[cur][chk]=++cnt;
            siz[cnt]=1;
            val[cnt]=v;
            fa[cnt]=cur;
            splay(cnt);
            break;
        }
        cur=ch[cur][chk];
    }
}
void dfs(int x=root){
    if(ch[x][0])dfs(ch[x][0]);
    cout<<val[x]<<' ';
    if(ch[x][1])dfs(ch[x][1]);
}
int main(){
    IOS;
    insert(0,7);
    insert(0,9);
    insert(0,8);
    insert(1,12);
    insert(4,1);
    insert(3,33);
    dfs();
}
