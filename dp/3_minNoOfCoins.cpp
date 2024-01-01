#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

// ONLY RECURSION
int solveRec(vector<int> &num, int x) {
    // base case
    if(x==0) return 0;
    if(x < 0) return INT_MAX;

    int mini = INT_MAX;
    for(int i=0; i<num.size(); i++) {
        int ans = solveRec(num, x-num[i]);
        if(ans != INT_MAX) 
            mini = min(mini, 1+ans);
    }
    return mini;
}
int minimumElements(vector<int> &num, int x) {
    int ans = solveRec(num, x);
    if(ans == INT_MAX) return -1;
    return ans;
}



// RECURSION + MEMOIZATION
int solveMem(vector<int> &num, int x, vector<int> &dp) {
    // base case
    if(x == 0) return 0;
    if(x < 0) return INT_MAX;
    // memoization
    if(dp[x] != -1) return dp[x];

    int mini = INT_MAX;
    for(int i=0; i<num.size(); i++) {
        int ans = solveMem(num, x-num[i], dp);
        if(ans != INT_MAX) 
            mini = min(mini, 1+ans);
    }
    dp[x] = mini;
    return mini;
}
int minimumElements(vector<int> &num, int x) {
    vector<int> dp(x+1, -1);
    int ans = solveMem(num, x, dp);
    if(ans == INT_MAX) return -1;
    else return ans;
}


// TABULATION -> BOTTOM-UP APPROACH
int solveTab(vector<int> &num, int x) {
    vector<int> dp(x+1, INT_MAX);
    // base case
    dp[0] = 0;
    for(int i=1; i<=x; i++) {
        // trying to solve for every amount figure from 1 to x
        for(int j=0; j<num.size(); j++) {
            if(i-num[j] >= 0 && dp[i-num[j]] != INT_MAX) {
                dp[i] = min(dp[i], 1+dp[i-num[j]]);
            }
        }
    }
    if(dp[x] == INT_MAX) return -1;
    return dp[x];
}
int minimumElements(vector<int> &num, int x) {
    return solveTab(num, x);
}