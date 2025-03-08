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
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e17;
LL siz[N],dfn[N],top[N],dep[N],son[N],fa[N],p[N],idfn[N];
int n,m;
int cnt;
vector<int> G[N];
void dfs1(int x, int f){
    fa[x]=f;
    siz[x]=1;
    dep[x]=dep[f]+1;
    for(int ne:G[x]){
        if(ne==f)continue;
        dfs1(ne, x);
        siz[x]+=siz[ne];
        if(siz[ne]>siz[son[x]])son[x]=ne;
    }
}
void dfs2(int x,int tp){
    top[x]=tp;
    dfn[x]=++cnt;
    idfn[cnt]=x;
    if(son[x])dfs2(son[x],tp);
    for(int ne:G[x]){
        if(ne==son[x]||ne==fa[x])continue;
        dfs2(ne,ne);
    }
}
struct P{
    LL sum=0;
    vector<pll> cs;
};
P operator+(const P&a,const P& b){
    if(a.cs.empty())return b;
    if(b.cs.empty())return a;
    P res;
    res.sum=a.sum+b.sum;
    for(int i=0;i<a.cs.size()-1;i++)res.cs.push_back(a.cs[i]);
    LL val=a.cs.back().first+a.sum;
    int ass=a.cs.back().second;
    bool has=false;
    for(int i=0;i<b.cs.size();i++){
        auto& c=b.cs[i];
        if(c.first>=val) {
            if(c.first>val&&!has){
                has=true;
                res.cs.emplace_back(a.cs.back().first,a.cs.back().second+(i?b.cs[i-1].second:0));
                res.cs.emplace_back(c.first - a.sum, ass + c.second);
            }else res.cs.emplace_back(c.first - a.sum, ass + c.second),has=true;
        }
    }
    if(b.cs.back().first<val)res.cs.emplace_back(a.cs.back().first,ass+b.cs.back().second);
    return res;
}
P tr[N*4],tl[N*4];
void update(int u){
    tl[u]=tl[ls]+tl[rs];
    tr[u]=tr[rs]+tr[ls];
}
void build(int u,int l,int r){
    if(l==r){
        LL val=p[idfn[l]];
        tr[u]=tl[u]={val,{{val,1}}};
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    update(u);
}
void change(int u,int l,int r,int pos,LL v){
    if(l==r){
        LL& val=p[idfn[l]];
        val=v;
        tr[u]=tl[u]={val,{{val,1}}};
        return;
    }
    if(pos<=mid)change(ls,l,mid,pos,v);
    else change(rs,mid+1,r,pos,v);
    update(u);
}
P query(int u,int l,int r,int L,int R,int op){
    if(L>R){
        P res;
        res.sum=0;
        return res;
    }
    if(L<=l&&R>=r){
        if(op)return tr[u];
        else return tl[u];
    }
    if(R<=mid)return query(ls,l,mid,L,R,op);
    if(L>mid)return query(rs,mid+1,r,L,R,op);
    if(!op)return query(ls,l,mid,L,R,op)+ query(rs,mid+1,r,L,R,op);
    else return query(rs,mid+1,r,L,R,op)+ query(ls,l,mid,L,R,op);
}
void modify(int x,LL val){
    change(1,1,n,dfn[x],val);
}
LL ask(int s,int t,LL k){
    P tpl,tpr;
    while(top[s]!=top[t]){
        if(dep[top[s]]>dep[top[t]]){
            tpl= tpl+query(1,1,n,dfn[top[s]],dfn[s],1);
            s=fa[top[s]];
        }else{
            tpr=query(1,1,n,dfn[top[t]],dfn[t],0)+tpr;
            t=fa[top[t]];
        }
    }
    if(dep[s]>dep[t]){
        tpl= tpl+query(1,1,n,dfn[t],dfn[s],1);
    }else tpr= query(1,1,n,dfn[s],dfn[t],0)+tpr;
    tpl=tpl+tpr;
    LL ans=0;
    for(auto& [a,b]:tpl.cs){
        if(k>=a)ans=b;
    }
    return ans;
}
signed main(){
    IOS;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    while(m--){
        int op;
        cin>>op;
        if(op==1){
            LL x,y;
            cin>>x>>y;
            modify(x,y);
        }else{
            LL s,t,k;
            cin>>s>>t>>k;
            cout<<ask(s,t,k)<<'\n';
        }
    }
}
