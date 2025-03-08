#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<queue>
#include <valarray>
#include <sstream>

using namespace std;
class Solution {
public:
    string toGoatLatin(string sentence) {
        vector<bool> yuan(300);
        yuan['a']=yuan['e']=yuan['i']=yuan['o']=yuan['u']=true;
        yuan['A']=yuan['E']=yuan['I']=yuan['O']=yuan['U']=true;
        function<string(string&,int)> calc=[&](string& s,int cnt)->string{
            string tpp(cnt,'a');
            if(yuan[s[0]]){
                return s+"ma1"+tpp;
            }
            else{
                string aa=s.substr(1);
                aa.push_back(s[0]);
                return aa+"ma1"+tpp;
            }
        };
     istringstream str(sentence);
     string res;
     string tp;
     int cnt=0;
     bool fst=true;
     while(str>>tp){
         if(fst)res+=calc(tp,++cnt),fst=false;
         else res+=" "+calc(tp,++cnt);
     }
        return res;
    }
};
int main(){
    Solution ss;
    cout<<ss.toGoatLatin("I speak Goat Latin");

}