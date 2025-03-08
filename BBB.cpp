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
struct P{
    LL lm,rm,mm,sum;
};
P dandian(LL x){
    P res;
    res.sum=x;
    chmax(x,0);
    res.lm=res.rm=res.mm=x;
    return res;
}
P operator+(P a,P b){
    P res;
    res.lm=max(a.lm,a.sum+b.lm);
    res.rm=max(b.rm,a.rm+b.sum);
    res.sum=a.sum+b.sum;
    res.mm=max(max(a.mm,b.mm),a.rm+b.lm);
    return res;
}
int cc;
void dfs1(int x,int f,
          vector<vector<int>>& G,
          vector<int>& siz,
          vector<int>&son,
          vector<int>&dep,
          vector<int>& fa){
    dep[x]=dep[f]+1;
    siz[x]=1;
    son[x]=0;
    fa[x]=f;
    for(int ne:G[x]){
        if(ne==f)continue;
        dfs1(ne,x,G,siz,son,dep,fa);
        siz[x]+=siz[ne];
        if(siz[ne]>siz[son[x]])son[x]=ne;
    }
}
void dfs2(int x,int tp,vector<int>& dfn,vector<int>& idfn,vector<vector<int>>& G,vector<int>& son,vector<int>& top,vector<int>& fa){
    top[x]=tp;
    dfn[x]=++cc;
    idfn[cc]=x;
    if(son[x])dfs2(son[x],tp,dfn,idfn,G,son,top,fa);
    for(int ne:G[x]){
        if(ne==fa[x]||ne==son[x])continue;
        dfs2(ne,ne,dfn,idfn,G,son,top,fa);
    }
}
vector<P> Build(vector<LL>& A){
    int n=A.size();
    n--;
    vector<P> res(n*4+4);
    function<void(int,int,int)> dfs=[&](int u,int l,int r)->void{
        if(l==r){
            res[u]= dandian(A[l]);
            return;
        }
        dfs(ls,l,mid);
        dfs(rs,mid+1,r);
        res[u]=res[ls]+res[rs];
    };
    return res;
}
P query(vector<P>& tr,int n,int ll,int rr){
    function<P(int,int,int,int,int)> dfs=[&](int u,int l,int r,int L,int R)->P{
        if(L<=l&&R>=r)return tr[u];
        if(R<=mid)return dfs(ls,l,mid,L,R);
        if(L>mid)return dfs(rs,mid+1,r,L,R);
        return dfs(ls,l,mid,L,R)+dfs(rs,mid+1,r,L,R);
    };
    return dfs(1,1,n,ll,rr);
}
void change(vector<P>&tr ,int n,int p,LL v){
    function<void(int,int,int,int,LL)> dfs=[&](int u,int l,int r,int p,LL v)->void{
        if(l==r){
            tr[u]= dandian(v);
            return;
        }
        p<=mid?dfs(ls,l,mid,p,v):dfs(rs,mid+1,r,p,v);
        tr[u]=tr[ls]+tr[rs];
    };
    dfs(1,1,n,p,v);
}
void Change(vector<P>& tr,int n,int id,LL v,vector<int>& dfn){
    int ii=dfn[id];
    change(tr,n,ii,v);
}
P Query(vector<P> & tr,int n,int x,int y,vector<int>& dfn,vector<int>& top,vector<int>& fa){
    P res;
    while(fa[x]){
        int tp=top[x];
        res=res+query(tr,n,dfn[tp],dfn[x]);
        x=fa[top[x]];
    }
    return res;
}
void solve(){
    int n,q;
    cin>>n>>q;
    vector<LL> A(n);
    cin>>A;
    A.insert(A.begin(),0ll);
    vector<vector<int>> global_G(n + 1);
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        global_G[u].emplace_back(v);
        global_G[v].emplace_back(u);
    }
    vector<int> loop;
    queue<int> Q;
    vector<int> du(n+1);
    for(int i=1;i<=n;i++)du[i]=global_G[i].size();
    for(int i=1;i<=n;i++)if(du[i]==1)Q.emplace(i);
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int ne:global_G[x]){
            du[ne]--;
            if(du[ne]==1){
                Q.emplace(ne);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(du[i]==2)loop.emplace_back(i);
    }
    set<int> S_loop;
    for(int i:loop)S_loop.insert(i);
    const int LP=loop.size();
    vector<int> FA(n+1);
    auto find=[&](int x)->int{
        while(x!=FA[x])x=FA[x]=FA[FA[x]];
        return x;
    };
    auto merge=[&](int x,int y)->void{
        x=find(x),y=find(y);
        if(x==y)return;
        if(du[x]==2)swap(x,y);
        FA[x]=y;
    };
    for(int i=1;i<=n;i++){
        for(int ne:global_G[i]){
            if(!S_loop.contains(i)||!S_loop.contains(ne))merge(i,ne);
        }
    }
    vector<int> _now(loop.size(),1);
    map<int,pii> Mp;
    vector<vector<int>> ID(LP);
    for(int i=0;i<loop.size();i++){
        Mp[loop[i]]={i,0};
        ID[i].emplace_back(loop[i]);
    }
    for(int i=1;i<=n;i++){
        if(!S_loop.contains(i)){
            int at=Mp[find(i)].first;
            Mp[i]={at,_now[at]++};
            ID[at].emplace_back(i);
        }
    }
    vector<vector<LL>> AA(loop.size());
    for(int i=0;i<loop.size();i++)AA[i].resize(_now[i]);
    for(int i=1;i<=n;i++){
        if(!S_loop.contains(i)){
            auto [at,id]=Mp[i];
            AA[at][id]=A[i];
        }
    }
    vector<vector<int>> dfn(LP),idfn(LP),top(LP),son(LP),siz(LP),fa(LP),dep(LP);
    vector<vector<vector<int>>> G(LP);
    for(int i=0;i<LP;i++){
        G[i].resize(_now[i]);
    }
    for(int i=1;i<=n;i++){
        for(int ne:global_G[i]){
            if(du[i]==2||du[ne]==2)continue;
            auto [at1,id1]=Mp[i];
            auto [at2,id2]=Mp[ne];
            assert(at1==at2);
            G[at1][id1].emplace_back(id2);
            G[at2][id2].emplace_back(id1);
        }
    }
    for(int i=0;i<loop.size();i++){

    }
}
signed main(){
    IOS;
    int _;
    cin>>_;
    while(_--)solve();
}
