#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
class Solution {
public:
    const static int mmm=5005;
    int h[mmm];
    vector<int> pre;
    vector<int> to;
    bool has[mmm];
    bool inq[mmm];
    string beg;
    vector<string> vec;
    int ds[mmm];
    int cnt=0;
    int fin=-1;
    int dis=-1;
    void add(int a,int b){
        pre.push_back(h[a]);
        h[a]=++cnt;
        to.push_back(b);
    }
    void bfs(){
        fill(ds,ds+mmm,-1);
        priority_queue<int> q;
        q.push(0);
        ds[0]=0;
        while(!q.empty()){
            int p=q.top();
            q.pop();
            if(p==fin) { break;}
            for(int j=h[p];j;j=pre[j]){
                int ne=to[j];
                if(ds[ne]==-1){
                    ds[ne]=ds[p]+1;
                    q.push(ne);
                }
            }
        }
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        pre.push_back(0);
        to.push_back(0);
        beg=beginWord;
        memset(inq,0,sizeof inq);
        memset(h,0,sizeof h);
        memset(has,0,sizeof has);
        int ll=wordList[0].size();
        int n=wordList.size();
        for(int i=0;i<n;i++){
            if(wordList[i]==beginWord){
                for(int j=i+1;j<n;j++){
                    wordList[j-1]=wordList[j];
                }
                n--;
                break;
            }
        }
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int ct=0;
                for(int y=0;y<ll;y++)
                    if(wordList[i][y]^wordList[j][y])ct++;
                if(ct==1)add(i+1,j+1),add(j+1,i+1);
            }
        }
        for(int i=0;i<n;i++){
            int ct=0;
            for(int y=0;y<ll;y++)
                if(beginWord[y]^wordList[i][y])ct++;
            if(ct==1)add(0,i+1);
        }
        for(int i=0;i<n;i++)
            if(endWord==wordList[i]){
                fin=i+1;
                break;
            }

        if(fin==-1)return 0;
        bfs();
        return ds[fin]+1;
    }
};
int main(){
    vector<string> S;
    string beg,end;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        S.push_back(s);
    }
    cin>>beg>>end;
    Solution ss;
    int res=ss.ladderLength(beg,end,S);
    cout<<res;
    return 0;
}