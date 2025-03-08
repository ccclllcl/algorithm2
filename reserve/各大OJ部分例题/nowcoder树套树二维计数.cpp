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
#define tll tuple<LL,LL,LL>
#define tii tuple<int,int,int>
#define plll pair<LLL,LLL>
#define LL long long
#define LLL __int128
#define ld long double
using namespace std;
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
const int N=6e5+5;
const int SIZ=1e7;
const LL inf=1e17;
struct P{
    int x,v;
    bool operator<(const P& o)const{
        return v<o.v;
    }
};
namespace sts{
    int n;
    int tr[N*100][2];
    int cnt;
    int root[N*4];
    int siz[N*100];
    int ss[N*4];
    void inner_insert(int& u,int l,int r,int y){
        if(!u)u=++cnt,siz[u]=0;
        siz[u]++;
        if(l==r){
            return;
        }
        int md=(l+r)>>1;
        if(y<=md)inner_insert(tr[u][0],l,md,y);
        else inner_insert(tr[u][1],md+1,r,y);
    }
    void insert(int u,int l,int r,int x,int y){
        ss[u]++;
        if(l==r){
            inner_insert(root[u],1,n,y);
            return;
        }
        int md=(l+r)>>1;
        if(x<=md)insert(ls,l,md,x,y);
        else insert(rs,md+1,r,x,y);
    }
    int nei_query(int& u,int l,int r,int L,int R){
        if(!u)return -1;
        if(siz[u]==0)return -1;
        if(l==r)return l;
        int res=-1;
        if(L<=mid)res= nei_query(tr[u][0],l,mid,L,R);
        if(res!=-1)return res;
        if(R>mid)res= nei_query(tr[u][1],mid+1,r,L,R);
        return res;
    }
    pii query(int u,int l,int r,int L,int R,pii v){
        if(l==r){
            int res= nei_query(root[u],1,n,v.first,v.second);
            if(res==-1)return {-1,-1};
            else{
                return {l,res};
            }
        }
        if(!ss[u])return {-1,-1};
        pii res={-1,-1};
        if(L<=mid)res= query(ls,l,mid,L,R,v);
        if(res.first!=-1)return res;
        if(R>mid)res= query(rs,mid+1,r,L,R,v);
        return res;
    }
    void nei_dele(int& u,int l,int r,int v){
        if(siz[u]==1){
            u=0;
            return;
        }
        siz[u]--;
        if(v<=mid)nei_dele(tr[u][0],l,mid,v);
        else nei_dele(tr[u][1],mid+1,r,v);
    }
    void dele(int u,int l,int r,int x,int y){
        ss[u]--;
        if(l==r){
            nei_dele(root[u],1,n,y);
            return;
        }
        if(x<=mid)dele(ls,l,mid,x,y);
        else dele(rs,mid+1,r,x,y);
    }
    void Insert(int x,int y){
        insert(1,1,n,x,y);
    }
    void Dele(int x,int y){
        dele(1,1,n,x,y);
    }
    pii ask_dele(int p,int q){
        pii res={-1,-1};
        if(p>1){
            if(q>1)res= query(1,1,n,1,p-1,{1,q-1});
            if(res.first!=-1){
                Dele(res.first,res.second);
                return res;
            }
            if(q<n)res= query(1,1,n,1,p-1,{q+1,n});
            if(res.first!=-1){
                Dele(res.first,res.second);
                return res;
            }
        }
        if(p<n){
            if(q>1) {
                res = query(1, 1, n, p + 1, n, {1, q - 1}); }
            if(res.first!=-1){
                Dele(res.first,res.second);
                return res;
            }
            if(q<n)res=query(1,1,n,p+1,n,{q+1,n});
            if(res.first!=-1){
                Dele(res.first,res.second);
                return res;
            }
        }
        return {-1,-1};
    }
}
signed main(){
    IOS;
    freopen("../out","w",stdout);
    int n;
    cin>>n;
    map<LL,int> mp;
    vector<pll> opo;
    for(int i=0;i<n;i++){
        LL a,b;
        cin>>a>>b;
        opo.emplace_back(a,b);
        mp[a]=1,mp[b]=1;
    }
    sts::n=0;
    for(auto& [k,v]:mp)v=++sts::n;
    map<int,LL> imp;
    for(auto& [k,v]:mp)imp[v]=k;
    for(auto& [a,b]:opo)a=mp[a],b=mp[b];
    priority_queue<P> q;
    map<int,int> M;
    map<pll,int> Mm;
    map<int,int> cnt;
    for(int i=0;i<n;i++){
        int a,b;
        a=opo[i].first,b=opo[i].second;
        cnt[a]++,cnt[b]++;
        if(a==b){
            M[a]++;
        }else{
            Mm[{a,b}]++;
            sts::Insert(a,b);
        }
    }
    for(auto& [k,v]:cnt){
        if(v>n+1){
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes\n";
    for(auto& [a,b]:M){
        q.push({a,b});
    }
    vector<pll> ans;
    while(!q.empty()){
        auto tp=q.top();q.pop();
        if(ans.empty()||ans.back().second!=tp.x){
            ans.emplace_back(tp.x,tp.x);
            if(tp.v>1)q.push({tp.x,tp.v-1});
        }else{
            if(!q.empty()){
                auto ttp=q.top();q.pop();
                q.push(tp);
                ans.emplace_back(ttp.x,ttp.x);
                if(ttp.v>1)q.push({ttp.x,ttp.v-1});
            }else{
                int v=ans.back().second;
                pii res;
                auto ne=Mm.upper_bound({v+1,-1});
                if(ne==Mm.end()){
                    ne=--Mm.lower_bound({v-1,1e6});
                }
                if(ne->first.first!=v&&ne->first.second!=v){
                    res=ne->first;
                    ne->second--;
                    if(!ne->second)Mm.erase(ne);
                    sts::Dele(ne->first.first,ne->first.second);
                }else {
                    res = sts::ask_dele(v,v);
                    Mm[res]--;
                    if(Mm[res]==0)Mm.erase(res);
                }
                ans.emplace_back(res);
                ans.emplace_back(tp.x,tp.x);
                if(tp.v>1)q.push({tp.x,tp.v-1});
            }
        }
    }
    for(auto& [k,v]:Mm){
        for(int _=0;_<v;_++)if(ans.empty()||ans.back().second!=k.first)ans.emplace_back(k);else ans.emplace_back(k.second,k.first);
    }
    for(auto& [a,b]:ans)a=imp[a],b=imp[b];
    for(auto& [a,b]:ans)cout<<a<<' '<<b<<'\n';
}
