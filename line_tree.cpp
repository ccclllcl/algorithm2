#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<cstring>
#include<iostream>
#include<set>
using namespace std;
class Solution {
public:
    int f[105][105];
    vector<int>*bx;
    bool eq(int l,int r){
        char c=(*bx)[l];
        for(int i=l+1;i<=r;i++){
            if(c^(*bx)[i])return false;
        }
        return true;
    }
    int removeBoxes(vector<int>& boxes) {
        bx=&boxes;
        int n=boxes.size();
        for(int i=0;i<n;i++)f[i][i]=1;
        for(int len=2;len<=n;len++){
            for(int st=0;st+len-1<n;st++){
                if(eq(st,st+len-1))f[st][st+len-1]=len*len;
                else{
                    int maxx=0;
                    for(int k=st;k<st+len-1;k++){
                        maxx=max(maxx,f[st][k]+f[k+1][st+len-1]);
                    }
                    f[st][st+len-1]=maxx;
                }
            }
        }
        return f[0][n-1];
    }
};