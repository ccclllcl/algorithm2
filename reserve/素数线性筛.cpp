#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e6+5;
int p[N];
int minp[N];
int maxp[N];
int cnt=0;
void init(){
    for(int i=2;i<N;i++){
        if(!minp[i])p[cnt++]=i,minp[i]=maxp[i]=i;
        for(int j=0;j<cnt&&p[j]*i<N;j++){
            int y=p[j]*i;
            minp[y]=p[j];
            maxp[y]=maxp[i];
            if(i%p[j]==0){
                break;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    int x;
    cin>>x;
    if(x==1){
        cout<<-1;
        return 0;
    }
    if(minp[x]==x){
        cout<<-1;
        return 0;
    }
    int la=x-maxp[x]+1;
    int ans=la;
    for(int y=la;y<x;y++){
        if(maxp[y]==y)continue;
        int g=y-maxp[y]+1;
        ans=min(ans,g);
    }
    cout<<ans;
}