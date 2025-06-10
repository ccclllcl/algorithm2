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
struct state{
    int len{},link{};
    std::map<int,int> next;
};
state st[NN*2];
int sz=0,last=0;
void sam_init(){
    st[0].len=0;
    st[0].link=-1;
    last=0;
}
LL ans=0;
void sam_extend(int c){
    int cur = ++sz;
    st[cur].len=st[last].len+1;
    int p=last;
    while(p!=-1&&!st[p].next.count(c)){
        st[p].next[c]=cur;
        p=st[p].link;
    }
    if(p==-1){
        st[cur].link=0;
    }else{
        int q=st[p].next[c];
        if(st[p].len+1==st[q].len){
            st[cur].link=q;
        }else{
            int clone=++sz;
            st[clone].len=st[p].len+1;
            st[clone].next=st[q].next;
            st[clone].link=st[q].link;
            while(p!=-1&&st[p].next[c]==q){
                st[p].next[c]=clone;
                p=st[p].link;
            }
            st[q].link=st[cur].link=clone;
        }
    }
    last=cur;
    ans+=st[cur].len-st[st[cur].link].len;
}
vector<int> res;
int n;
void dfs(int x){
    if(res.size()==n)return;
    auto it=st[x].next.begin();
    res.emplace_back(it->first);
    dfs(it->second);
}
signed main(){
    IOS;
    cin>>n;
    vector<int> A(n);
    cin>>A;
    A.insert(A.end(),all(A));
    sam_init();
    for(int i:A)sam_extend(i);
    dfs(0);
    cout<<res;
}
