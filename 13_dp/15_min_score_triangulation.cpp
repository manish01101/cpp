#include<bits/stdc++.h>
using namespaces std;

/*
sol(i,j) = v[i]*v[k]*v[j] + solve(i,k) + solve(k, j)
*/

int solve(vector<int>& v, int i, int j) {
	// base case
	if (i + 1 == j)
		return 0;
	int ans = INT_MAX;
	for (int k = i + 1; k < j; k++) {
		ans = min(ans, v[i] * v[k] * v[j] + solve(v, i, k) + solve(v, k, j));
	}
	return ans;
}


int solveMem(vector<int>& v, int i, int j, vector<vector<int>>& dp) {
	// base case
	if (i + 1 == j)
		return 0;
	if (dp[i][j] != -1) {
		return dp[i][j];
	}
	int ans = INT_MAX;
	for (int k = i + 1; k < j; k++) {
		ans = min(ans, v[i] * v[k] * v[j] + solveMem(v, i, k, dp) + solveMem(v, k, j, dp));
	}
	dp[i][j] = ans;
	return dp[i][j];
}


int solveTab(vector<int>& v) {
	int n = v.size();
	vector<vector<int>> dp(n, vector<int>(n, 0));

	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 2; j < n; j++) { // j= i+2 so that there will be atleast 3 nodes
			int ans = INT_MAX;
			for (int k = i + 1; k < j; k++) {
				ans = min(ans, v[i] * v[k] * v[j] + dp[i][k] + dp[k][j]);
			}
			dp[i][j] = ans;
		}
	}
	return dp[0][n - 1];
}


int minScoreTriangulation(vector<int>& values) {
	int n = values.size();
	/* -- rec -- */
	// return solve(values, 0, n-1);

	/* -- rec + mem -- */
	// vector<vector<int>> dp(n, vector<int>(n, -1));
	// return solveMem(values, 0, n - 1, dp);

	/* -- tabulation -- */
	return solveTab(values);
}