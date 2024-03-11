#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define ls ((u)<<1)
#define rs ((u)<<1|1)
#define mid (((l)+(r))>>1)
#define lowbit(x) ((x)&(-(x)))
#define itn int
#define asn ans
#define reisze resize
#define pll pair<LL,LL>
#define pii pair<int,int>
#define LL long long
using namespace std;
constexpr int N=3e5+5;
const int SIZ=1e7;
constexpr LL inf=1e12;
int n;
vector<string> arr;
vector<vector<int>> NNe;
int fa[30];
int find(int x){
    return x==fa[x]?x:find(fa[x]);
}
void makeNN(int q){
    vector<int>& Next=NNe[q];
    string& T=arr[q];
    Next.push_back(-1);
    for(int i = 0, j = -1; i < T.size();){
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            if (i != T.size() && T[j] == T[i]) Next.push_back(Next[j]);//Next数组优化为Nextval数组
            else Next.push_back(j);
        }
        else j = Next[j];  //向前减少字符匹配量
    }
}
bool isnei(int zi,int mu){
    vector<int>& Next=NNe[zi];
    string & S=arr[mu];
    string& T=arr[zi];
    for (int i = 0, j = 0; i < S.size() && j < (int)T.size();){
        if (j == -1 || S[i] == T[j]) {
            i++, j++;
            if (j == T.size()) {
                return true;
            }
        }
        else j = Next[j];
    }
    return false;
}
vector<int> KMP(const string& S, const string& T){
    vector<int> Next;  //回溯指针  j和Next[j]之间的关系是j前面有若干个字符组成的串与[0,Next[j]-1]相同
    Next.push_back(-1);
    for(int i = 0, j = -1; i < T.size();){
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            if (i != T.size() && T[j] == T[i]) Next.push_back(Next[j]);//Next数组优化为Nextval数组
            else Next.push_back(j);
        }
        else j = Next[j];  //向前减少字符匹配量
    }

    vector<int> res;
    for (int i = 0, j = 0; i < S.size() && j < (int)T.size();){
        if (j == -1 || S[i] == T[j]) {
            i++, j++;
            if (j == T.size()) {
                res.push_back(i - j);
                j = Next[j];
            }
        }
        else j = Next[j];
    }
    return res;
}
vector<int> ff;
LL diss(int p,int q){
    string T=arr[p]+arr[q];
    vector<int> Next;  //回溯指针  j和Next[j]之间的关系是j前面有若干个字符组成的串与[0,Next[j]-1]相同
    Next.push_back(-1);
    for(int i = 0, j = -1; i < T.size();){
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            Next.push_back(j);
        }
        else j = Next[j];  //向前减少字符匹配量
    }
    return Next[T.size()];
}
struct P{
    int x;
    LL l;
};
vector<P> G[40];
int cc;
int too[40];
LL weight[40][40];
LL sum;
signed main(){
    IOS;
    cin>>n;
    arr.resize(n+1);
    NNe.resize(n+1);
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++)cin>>arr[i];
    for(int i=1;i<=n;i++){
        makeNN(i);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(j==i)continue;
            if(fa[j]!=j)continue;
            if(isnei(i,j)){
                fa[i]=j;
            }
        }
    }
    for(itn i=1;i<=n;i++)if(fa[i]==i)ff.push_back(i),sum+=arr[i].size();
    if(ff.empty()){
        int mm=0;
        for(int i=1;i<=n;i++)mm=max(mm,(int)arr[i].size());
        cout<<mm;
        return 0;
    }
    n=ff.size();
    for(int i=0;i<n;i++){
        too[ff[i]]=cc++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j==i)continue;
            LL v=diss(ff[i],ff[j]);
            weight[too[ff[j]]][too[ff[i]]]=-v;
//            G[too[ff[j]]].push_back({too[ff[i]],v});
        }
    }
    LL ans=INT_MAX;
    vector<vector<LL>> f(1<<cc,vector<LL>(cc));
    for(int cs=0;cs<1;cs++){
        for(int i=0;i<1<<cc;i++)for(int j=0;j<n;j++)f[i][j]=INT_MAX;
        for(int u=0;u<n;u++)f[1<<u][u]=0;
        for(int i = 0;i < (1 << n);i++){
            for(int j = 0;j < n;j++){
                if(i >> j & 1){
                    for(int k = 0;k < n;k++){
                        if(i - (1 << j) >> k & 1){
                            f[i][j] = min(f[i][j], f[i - (1 << j)][k] + weight[k][j]);
                        }
                    }
                }
            }
        }
        for(int i=0;i<n;i++)ans=min(ans,f[(1<<n)-1][i]);
    }
    for(int i=0;i<n;i++){
        LL v=f[(1<<n)-1][i];
        ans=min(ans,v);
    }
    cout<<sum+ans;
}
