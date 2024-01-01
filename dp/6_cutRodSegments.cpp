#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

// RECURSION
int solve(int n, int x, int y, int z) {
    // base case
    if(n == 0) return 0;
    if(n < 0) return INT_MIN;
    
    int a = solve(n-x, x, y, z) + 1;
    int b = solve(n-y, x, y, z) + 1;
    int c = solve(n-z, x, y, z) + 1;

    int ans = max(a, max(b, c));
    return ans;
}
int cutSegments(int n, int x, int y, int z) {
    int ans = solve(n, x, y, z);
    if(ans < 0) return 0;
    else return ans;
}


// RECURSION + MEMOIZATION
int solveMem(int n, int x, int y, int z, vector<int> &dp) {
    // base case
    if(n==0) return 0;
    if(n < 0) return INT_MIN;

    if(dp[n] != -1) return dp[n];
    int b = solveMem(n-y, x, y, z, dp) + 1;
    int a = solveMem(n-x, x, y, z, dp) + 1;
    int c = solveMem(n-z, x, y, z, dp) + 1;

    dp[n] = max(a, max(b, c));
    return dp[n];
}
int cutSegments(int n, int x, int y, int z) {
    vector<int> dp(n+1, INT_MIN);
    int ans = solveMem(n, x, y, z, dp);
    if(ans < 0) return 0;
    else return ans;
}


// TABULATION
int solveTab(int n, int x, int y, int z) {
    vector<int> dp(n+1, INT_MIN);
    dp[0] = 0;

    for(int i=1; i<=n; i++) {
        if(i-x >= 0) 
            dp[i] = max(dp[i], dp[i-x] + 1);
        if(i-y >= 0) 
            dp[i] = max(dp[i], dp[i-y] + 1);
        if(i-z >= 0) 
            dp[i] = max(dp[i], dp[i-z] + 1);
    }
    // OR
    // this is even better than upper one
    for(int i=1; i<=n; i++) {
        if(i-x >= 0 && dp[i-x] != -1) 
            dp[i] = max(dp[i], dp[i-x] + 1);
        if(i-y >= 0 && dp[i-y] != -1) 
            dp[i] = max(dp[i], dp[i-y] + 1);
        if(i-z >= 0 && dp[i-z] != -1) 
            dp[i] = max(dp[i], dp[i-z] + 1);
    }
}
int cutSegmets(int n, int x, int y, int z) {
    int ans = solveTab(n, x, y, z);
    if(ans < 0) return 0;
    else return ans;
}