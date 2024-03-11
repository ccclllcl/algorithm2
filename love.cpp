#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;
class MajorityChecker {
public:
    typedef long long LL;
    const int N=1e7;
    const int L=1,R=2e4;
    vector<int> ls,rs,siz;
    int cnt=0;
    vector<int> root;
    map<LL,int> M;
    int n;
    LL base=2e4;
    bool qk=false;
    int yy;
    vector<int> tp;
    LL calc(LL a,LL b,LL c){
        return a*base*base+b*base+c;
    }
    void change(int &u,int v,int l,int r,int p){
        u=++cnt;
        if(l==r){
            siz[u]=siz[v]+1;
            return;
        }
        ls[u]=ls[v];rs[u]=rs[v];
        int mid=(l+r)>>1;
        if(p<=mid)change(ls[u],ls[v],l,mid,p);
        else change(rs[u],rs[v],mid+1,r,p);
        siz[u]=siz[ls[u]]+siz[rs[u]];
    }
    int query2(int a,int b,int l,int r,int th){
        if(siz[a]-siz[b]<th)return 0;
        if(l==r){
            return l;
        }
        int mid=(l+r)>>1;
        int ll=query2(ls[a],ls[b],l,mid,th);
        int rr= query2(rs[a],rs[b],mid+1,r,th);
        return ll+rr;
    }
    MajorityChecker(vector<int>& arr) {
        ls=vector<int>(N);
        rs=vector<int>(N);
        siz=vector<int>(N);
        n=arr.size();
        root=vector<int>(n+1);
        for(int i=1;i<=n;i++)change(root[i],root[i-1],L,R,arr[i-1]);
        for(int i=0;i<n-1;i++)if(arr[i]^arr[i+1])qk=true;
        yy=arr[0];
        tp=arr;
    }
    int query3(int l,int r,int th){
        unordered_map<int,int> M;
        for(int i=l;i<=r;i++)M[tp[i]]++;
        int maxx=-1;
        for(auto& [k,v]:M)
            if(v>=th)maxx=max(maxx,v);
        return maxx;
    }
    int query(int left, int right, int threshold) {
        if(threshold>right-left+1)return -1;
        if(threshold>=n&&qk)return -1;
        if(!qk)return yy;
        LL v= calc(left,right,threshold);
        if(M.count(v))return M[v];
        if(right-left<10){
            int val= query3(left,right,threshold);
            M[v]=val?val:-1;
            return val?val:-1;
        }
        int val= query2(root[right+1],root[left],L,R,threshold);
        M[v]=val?val:-1;
        return val?val:-1;
    }
};

int main(){
    vector<int> p={2, 3, 1, 1, 1};
    MajorityChecker ss(p);
    cout<<ss.query(0,4,3)<<endl;
    cout<<ss.query(1,3,2)<<endl;
//    cout<<ss.query1(2,3,2)<<endl;
}