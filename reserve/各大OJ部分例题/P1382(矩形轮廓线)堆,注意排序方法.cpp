#include<bits/stdc++.h>
#define LL long long
using namespace std;
struct P{
    LL x;
    LL v;
    bool operator<(P o)const{
        if(x!=o.x)return x<o.x;
        return v>o.v;
    }
};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<P> A;
    for(int i=0;i<n;i++){
        LL l,r,h;
        cin>>h>>l>>r;
        A.push_back({l,h});
        A.push_back({r,-h});
    }
    priority_queue<LL> q;
    vector<P> ans;
    map<LL,LL> M;
    sort(A.begin(),A.end());
    LL la=0;
    for(int i=0;i<2*n;i++){
        P tp=A[i];
        if(tp.v>0){
            q.push(tp.v);
        }else{
            M[-tp.v]++;
            while(!q.empty()&&M[q.top()])M[q.top()]--,q.pop();
        }
        LL now=q.empty()?0:q.top();
        if(now!=la){
            ans.push_back({tp.x,la});
            ans.push_back({tp.x,now});
            la=now;
        }
    }
    cout<<ans.size()<<'\n';
    for(P tp:ans){
        cout<<tp.x<<' '<<tp.v<<'\n';
    }
}