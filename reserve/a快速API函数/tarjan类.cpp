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
const int N=3e5+5;
const int SIZ=1e7;
const LL inf=1e17;
vector<int> G[N];
int n,m;
int dfn[N],low[N];
int cnt=0;
//无向图求割边
void dfs(int x,int f){
    dfn[x]=low[x]=++cnt;
    for(int ne:G[x]){
        if(!dfn[ne]){
            dfs(ne,x);
            low[x]=min(low[ne],low[x]);
            if(low[ne]>dfn[x]){
                //x->ne这条边为割边(桥)
            }
        }else if(ne!=f){
            low[x]=min(low[x],dfn[ne]);
        }
    }
}
