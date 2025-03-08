#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#define LL long long
#define pll pair<LL, LL>
typedef __gnu_pbds::tree<pll, __gnu_pbds::null_type, std::less<pll>,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update>
        RBTree;
LL inf=1e9;
const int N=2e5+5;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    RBTree rbt;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        LL op,x;
        cin>>op>>x;
        switch (op) {
            case 1:
                rbt.insert({x,i});
                break;
            case 2:
                rbt.erase(rbt.upper_bound({x,0}));
                break;
            case 3:
                cout<<rbt.order_of_key({x,0})+1<<'\n';
                break;
            case 4:
                cout<<rbt.find_by_order(x-1)->first<<'\n';
                break;
            case 5: {
                auto ptr = --rbt.lower_bound({x, 0});
                cout << ptr->first << '\n';
                break;
            }
            case 6:
                auto pt=rbt.upper_bound({x,inf});
                cout<<pt->first<<'\n';
                break;
        }
    }
}