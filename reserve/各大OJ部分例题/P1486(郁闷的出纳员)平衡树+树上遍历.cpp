#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
#define LL long long
#define pll pair<LL,LL>
const int N=3e5+5;
LL inf=1e12;
typedef __gnu_pbds::tree<pll, __gnu_pbds::null_type, std::greater<>,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update>
        RBTree;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    RBTree tre;
    LL n,mi;
    LL now;
    cin>>n>>mi;
    now=mi;
    LL lea=0;
    for(int _=1;_<=n;_++){
        char c;
        cin>>c;
        LL k;
        cin>>k;
        if(c=='I'){
            if(k>=mi){
                tre.insert({k-mi+now,_});
            }
        }else if(c=='A'){
            now-=k;
        }else if(c=='S'){
            now+=k;
            auto pt=--tre.end();
            while(tre.size()&&pt->first<now){
                auto pre=pt--;
                tre.erase(pre);
                lea++;
            }
        }else{
            if(k>tre.size()){
                cout<<-1<<'\n';
            }else{
                auto tp=tre.find_by_order(k-1);
                cout<<tp->first-now+mi<<'\n';
            }
        }
    }
    cout<<lea<<'\n';
}
