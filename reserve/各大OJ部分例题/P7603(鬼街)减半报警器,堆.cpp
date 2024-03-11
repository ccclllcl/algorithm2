#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=1e5+5;
int n,m;
struct P{
    int x;  //堆中P的x记录所属报警器,H数组中的x记录对应的质数
    LL v;
    bool operator<(P o)const{
        return v>o.v;
    }
};
priority_queue<P> q[N];   //启发式报警器,当某个单点的增量到达某一程度,测试对应报警器是否需要报警
vector<vector<P>> H;  //记录各个报警器上一次判断时刻的各单点累积量,方便下一次判断时与val做差值来消耗剩余所需量M
vector<LL> M;
LL val[N];  //记录当前时刻各个单点的累积量
int p[N];
int pre[N];
int cnt=0;
void init(){
    for(int i=2;i<N;i++){
        if(!pre[i])pre[i]=i,p[cnt++]=i;
        for(int j=0;j<cnt&&p[j]*i<N;j++){
            pre[p[j]*i]=p[j];
            if(i%p[j]==0)break;
        }
    }
}
vector<int> get_prime(int x){
    vector<int> res;
    while(x!=1){
        if(res.empty()||res.back()!=pre[x])res.push_back(pre[x]);
        x/=pre[x];
    }
    return res;
}
vector<int> ans;
bool has[N];
void Ring(int x){
    for(auto& tp:H[x]){
        M[x]-=val[tp.x]-tp.v,tp.v=val[tp.x];
    }
    if(M[x]<=0){
        ans.push_back(x);
        has[x]=true;
    }
    else{
        int len=H[x].size();
        LL ad=(M[x]+len-1)/len;
        for(auto &tp:H[x])q[tp.x].push({x,tp.v+ad});
    }
}
void add(int x,LL v){
    vector<int> pri= get_prime(x);
    for(int i:pri)val[i]+=v;
    for(int i:pri){
        while(!q[i].empty()&&q[i].top().v<=val[i]){
            if(!has[q[i].top().x])Ring(q[i].top().x);
            q[i].pop();
        }
    }
}
int main(){
    init();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    LL k=0;
    for(int _=0;_<m;_++){
        int op;
        cin>>op;
        LL x,y;
        cin>>x>>y;
        y^=k;
        if(op){
            vector<int> res= get_prime(x);
            int n1=res.size();
            vector<P> h(n1);
            int id=H.size();
            for(int i=0;i<n1;i++)h[i]={res[i],val[res[i]]};
            H.emplace_back(h);
            M.push_back(y);
            Ring(id);
        }else{
            add(x,y);
            int n1=ans.size();
            cout<<n1<<' ';
            k=n1;
            sort(ans.begin(),ans.end());
            for(int i:ans)cout<<i+1<<' ';
            cout<<'\n';
            ans.clear();
        }
    }
}