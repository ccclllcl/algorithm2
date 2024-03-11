#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<cstring>
#include<bitset>
#include<math.h>
#include <random>
#include<unordered_set>
#include <set>
#include<tuple>
using namespace std;
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>> dp(n+1,vector<int>(n+1));
        int s=0;
        for(int i:nums)if(i==3)s++;
        dp[0][0]=n-s;
        for(int i=0;i<=n;i++){
            if(i) {
                dp[i][i] = dp[i - 1][i - 1];
                if (nums[i - 1] == 1)dp[i][i]--;
                if (nums[i - 1] == 3)dp[i][i]++;
            }
            for(int j=i+1;j<=n;j++){
                dp[i][j]=dp[i][j-1];
                if(nums[j-1]==2)dp[i][j]--;
                if(nums[j-1]==3)dp[i][j]++;
            }
        }
        int minn=dp[0][0];
        for(int i=0;i<=n;i++)
            for(int j=i;j<=n;j++)
                minn=min(minn,dp[i][j]);
        return minn;
    }
};
int main(){
    ios::sync_with_stdio(false);
    Solution ss;
    vector<int> p={2,1,3,2,1};
    cout<<ss.minimumOperations(p);

}