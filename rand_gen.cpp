#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
int main(){
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    auto uni=uniform_int_distribution<int>(1, N);
    freopen("../in.txt","w",stdout);
    cout<<1<<'\n';
    int n=N;
    cout<<n<<'\n';
    for(int i=1;i<=n;i++)cout<<uni(rng)<<' ';
}