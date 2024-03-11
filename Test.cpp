#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<cstring>
#include<bitset>
#include<math.h>
#include <random>
#include <set>
#include<unordered_set>
using namespace std;
class Solution {
public:
    map<string,int> M;
    string tb[5]={"R","Y","B","G","W"};
    char tbb[5]={'R','Y','B','G','W'};
    void make(string& s){
        if(s.size()<8)return;
        while(1){
            bool ok=true;
            for(int i=0;i<5;i++){
                for(int l=5;l<s.size();l++){
                    if(s[l]^tbb[i])continue;
                    int r=l;
                    for(;s[r]==tbb[i]&&r<s.size();r++);
                    if(r<s.size()){
                        if(r-l>2){
                            s=s.substr(0,l)+s.substr(r);
                            ok= false;
                        }
                    }else{
                        if(r-l>2){
                            s=s.substr(0,l);
                            ok= false;
                        }
                    }
                }
            }
            if(ok)break;
        }
    }

    int dfs(string s){
        if(s.size()==5)return 0;
        if(M.count(s))return M[s];
        int ans=1e9;
        for(int i=0;i<5;i++){
            if(s[i]^'0'){
                s[i]--;
                for(int j=5;j<=s.size();j++){
                    string tpp=s.substr(0,j)+tb[i]+s.substr(j);
                    make(tpp);
                    int res=dfs(tpp);
                    if(~res)ans=min(ans,res+1);
                }
                s[i]++;
            }
        }
        if(ans==1e9){
            return M[s]=-1;
        }else{
            return M[s]=ans;
        }
    }
    int findMinStep(string board, string hand) {
        map<char,int> cnt;
        for(char c:hand){
            cnt[c]++;
        }
//        map<char,int>c2;
//        for(char c:board){
//            c2[c]++;
//        }
//        for(int i=0;i<5;i++){
//            cc[tbb[i]]=min(cc[tbb[i]],c2[tbb[i]]*2);
//        }
        string fn=to_string(cnt['R'])+to_string(cnt['Y'])+to_string(cnt['B'])+to_string(cnt['G'])+to_string(cnt['W'])+board;
        return dfs(fn);
    }
};
int main(){

    Solution ss;
    cout<<ss.findMinStep("RRYGGYYRRYYGGYRR","GGBBB");
}