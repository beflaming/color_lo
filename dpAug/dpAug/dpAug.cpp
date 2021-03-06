// dpAug.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<iostream>
using namespace std;

/* 669.Coin change, classical DP. f(num+1); f[i]=min(f[i-1]+1); f[i-coins[j]]+1, f[i]; 
coin Change  (i=1;i<=amnount;++i); i>=coins[j]; */
class Solution669 {
public:
	int coinChange(vector<int> &coins, int amount){
		vector<int> f(amount+1);
		int i, j;

		f[0] = 0;
		for (i = 1; i<=amount;++i) {
			f[i] = -1;
			for (j = 0; j < coins.size();++j) {
				if (i >= coins[j] && f[i - coins[j]] != -1) {
					if (f[i] == -1 || f[i - coins[j]] + 1 < f[i]) {
						f[i] = f[i - coins[j]] + 1;
					}
				}
			}
		}
		return f[amount];
	}
};

/*740. Coin Change 2; to compute the number of combinations that make up that amount. 
You may assume that you have infinite number of each kind of coin.
*/
class Solution740 {
public:
	int change(vector<int> &coins, int amount) {
		vector<int> dp(amount+1);
		dp[0] = 1;
		for (int i = 0; i < coins.size();++i) {
			for (int j = coins[i]; j <=amount;++j) {
				dp[j] += dp[j - coins[i]];
			}
		}
		return dp[amount];
	}
};

/* unique path I. either down or right at any point in time. 
114. The robot is trying to reach the bottom-right corner of the grid.
*/
class Solution114 {
public:
	int uniquePaths(int m, int n) {
		// write your code here
		if (m == 0 || n == 0) return 1;
		vector<vector<int>> dp(m+1, vector<int>(n+1));
		dp[0][0] = 1;

		for (int i = 1; i<m; ++i) dp[i][0] = 1;
		for (int j = 1; j<n; ++j) dp[0][j] = 1;

		for (int i = 1; i<m; ++i) {
			for (int j = 1; j<n; ++j) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};
/* unique path II. 
115. if some obstacles are added to the grids. How many unique paths would there be?
*/
class Solution115 {
public:
	int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
		// write your code here
		int m = obstacleGrid.size();
		int n = m>0 ? obstacleGrid[0].size() : 0;

		if (m == 0 || n == 0 || obstacleGrid[0][0] == 1) return 0;

		vector<vector<int>> dp(m + 1, vector<int>(n + 1));
		dp[0][0] = 1;
		for (int i = 1; i<m; ++i) {
			if (obstacleGrid[i][0] == 1) {
				dp[i][0] = 0;
			}
			else {
				dp[i][0] = dp[i - 1][0];
			}
		}

		for (int j = 1; j<n; ++j) {
			if (obstacleGrid[0][j] == 1) {
				dp[0][j] = 0;
			}
			else {
				dp[0][j] = dp[0][j - 1];
			}
		}

		for (int i = 1; i<m; ++i) {
			for (int j = 1; j<n; ++j) {
				if (obstacleGrid[i][j] == 1) {
					dp[i][j] = 0;
				}
				else {
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		return dp[m - 1][n - 1];
	}
};

/* unique path III.
679. each grid contains a value, so each path also has a value. Find the sum of all the unique values paths.

*/
class Solution679 {
public:
	int uniqueWeightedPaths(vector<vector<int>> &grid) {
		int m = grid.size();
		int n = grid[0].size();
		if (m == 0 || n == 0) return 0;
		unordered_map<int, unordered_set<int>> mp;
		mp[0].insert(grid[0][0]);
		for (int i = 1; i < m;++i) {
			int cur = i * n;
			int prev = (i - 1)*n;
			for (auto dis:mp[prev]) {
				mp[cur].insert(dis+grid[i][0]);
			}
		}

		for (int j = 1; j < n; ++j) {
			int cur = j;
			int prev = j-1;
			for (auto dis : mp[prev]) {
				mp[cur].insert(dis + grid[0][j]);
			}
		}

		for (int i = 1; i < m;++i) {
			for (int j = 1; j < n; ++j) {
				int cur = i * n + j;
				int left = i * n + j - 1;
				int up = (i - 1)*n + j;
				for (auto dis : mp[left]) {
					mp[cur].insert(dis + grid[i][j]);
				}
				for (auto dis : mp[up]) {
					mp[cur].insert(dis + grid[i][j]);
				}
			}
		}

		int res = 0;
		int index = (m - 1)*n + n - 1;
		for (int dis:mp[index]) {
			res += dis;
		}
		return res;
	}
};

/* Unique Path IV.
1543. Give two integers to represent the height and width of the grid. 
The starting point is in the upper left corner and the ending point is in the upper right corner. 
You can go to the top right, right or bottom right. 
Find out the number of paths you can reach the end. And the result needs to mod 1000000007.
input:
height = 3
width = 3
output:
2
*/
class Solution1543 {
public:
	int uniquePathIV(int height, int width){
	}
};

/* 4 
*/

/* 116. Jump Game. 
This problem have two method which is Greedy and Dynamic Programming.
The time complexity of Greedy method is O(n).
The time complexity of Dynamic Programming method is O(n^2).
i.e. A = [2,3,1,1,4], return true.
     A = [3,2,1,0,4], return false.
*/
class Solution116 {
public:
	bool canJump(vector<int> &A) { //dp 
		int len = A.size();
		vector<bool> dp(len);

		dp[0] = true;
		for (int j = 1; j < len;++j) {
			dp[j] = false;
			for (int i = 0; i < j;++i) {
				if (dp[i] && i + A[i] >= j) {
					dp[j] = true;
					break;
				}
			}
		}
		return dp[len - 1];
	}
};
/* 117. Jump Game II
reach the last index in the minimum number of jumps.
A = [2,3,1,1,4]
The minimum number of jumps to reach the last index is 2. 
(Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/
class Solution117 {
public:
	int jumpMinI(vector<int> &A) {  //greedy
		int n = A.size(), res=0, pre=0, cur=0;
		while (cur<n-1) {
			++res;
			pre = cur;
			for (int i = 0; i <= pre;++i) {
				cur = max(cur, i + A[i]);
			}
			if (pre == cur) return -1;
		}
		return res;
	}

	int jumpMinII(vector<int> &A) {
		int n = A.size(), res = 0, pre = 0, cur = 0;
		for (int i = 0; i < n - 1;++i) {
			cur = max(cur, i+A[i]);
			if (i==pre) {
				++res;
				pre = cur;
				if (cur >= n - 1) break;
			}
		}
		return res;
	}
};

/* 622. Frog Jump
青蛙如果上一次跳了k距离，那么下一次只能跳k-1, k, 或k+1的距离，那么青蛙跳到某个石头上可能有多种跳法，
判断青蛙是否能跳到最后一个石头上，并没有让我们返回所有的路径，这样就降低了一些难度。
Way 1:
可以用递归来做，我们维护一个哈希表，建立青蛙在pos位置和拥有jump跳跃能力时是否能跳到对岸。
为了能用一个变量同时表示pos和jump，我们可以将jump左移很多位并或上pos，由于题目中对于位置大小有限制，所以不会产生冲突。
还是首先判断pos是否已经到最后一个石头了，是的话直接返回true；
然后看当前这种情况是否已经出现在哈希表中，是的话直接从哈希表中取结果。
如果没有，我们就遍历余下的所有石头，对于遍历到的石头，我们计算到当前石头的距离dist，如果距离小于jump-1，我们接着遍历下一块石头；
如果dist大于jump+1，说明无法跳到下一块石头，m[key]赋值为false，并返回false；
如果在青蛙能跳到的范围中，我们调用递归函数，以新位置i为pos，距离dist为jump，
如果返回true了，我们给m[key]赋值为true，并返回true。如果结束遍历我们给m[key]赋值为false，并返回false
Way 2:
dp[i]表示在位置为i的石头青蛙的弹跳力(只有青蛙能跳到该石头上，dp[i]才大于0)，
由于题目中规定了第一个石头上青蛙跳的距离必须是1，第一块石头上的弹跳力初始化为0(青蛙最远能到其弹跳力+1的距离，可以到达第二块石头)。
变量k表示当前石头，然后开始遍历剩余的石头，对于遍历到的石头i，我们来找到刚好能跳到i上的石头k，
如果i和k的距离大于青蛙在k上的弹跳力+1，则说明青蛙在k上到不了i，则k自增1。我们从k遍历到i，
如果青蛙能从中间某个石头上跳到i上，我们更新石头i上的弹跳力和最大弹跳力。
这样当循环完成后，我们只要检查最后一个石头上青蛙的最大弹跳力是否大于0即可，
*/
class Solution622 {
public:
	bool canCross(vector<int> &stones) { //way 2:
		unordered_map<int, unordered_set<int>> m;
		vector<int> dp(stones.size(),0);  //can jump
		m[0].insert(0);
		int k = 0; //current stone
		for (int i = 1; i < stones.size();++i) {
			while (dp[k] + 1 < stones[i] - stones[k]) ++k;
			for (int j = k; j < i;++j) {
				int t = stones[i] - stones[j];
				if (m[j].count(t - 1) || m[j].count(t) || m[j].count(t + 1)) {
					m[i].insert(t);
					dp[i] = max(dp[i],t);
				}
			}
		}
		return dp.back() > 0;
	}
};

/* Maximum Product SubArray in Mod 
*/
class Solution1403 {
public:
	void dfs(int x, int f, vector<vector<int>> &g, vector<int> &d, long long mul, long long &ans, bool &isMod) {
		bool isLeaf = true;
		int mod = 1e9 + 7;
		long long nxMul = (mul*d[x - 1] % mod + mod) % mod;
		for (int i = 0; i < g[x].size();++i) {
			int y = g[x][i];
			if (y == f) continue;
			isLeaf = false;
			dfs(y,x,g,d,nxMul,ans,isMod);
		}
		if (isLeaf) {
			if (isMod) {
				ans = max(ans,nxMul);
			}
			else {
				ans = nxMul;
				isMod = true;
			}
		}
	}
	int getProduct(vector<int> &x,vector<int> &y,vector<int> &d) {
		int n = d.size();
		vector<vector<int>> g(n+1);
		for (int i = 0; i < x.size();++i) {
			g[x[i]].push_back(y[i]);
			g[y[i]].push_back(x[i]);
		}
		long long ans;
		bool isMod = false;
		dfs(1,-1,g,d,1,ans,isMod);
		return ans;
	}
};

int main()
{
    return 0;
}

