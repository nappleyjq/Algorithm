/*
http://poj.org/problem?id=2385

Apple Catching

Description
It is a little known fact that cows love apples. Farmer John has two apple trees (which are conveniently numbered 1 and 2) in his field, each full of apples. Bessie cannot reach the apples when they are on the tree, so she must wait for them to fall. However, she must catch them in the air since the apples bruise when they hit the ground (and no one wants to eat bruised apples). Bessie is a quick eater, so an apple she does catch is eaten in just a few seconds.

Each minute, one of the two apple trees drops an apple. Bessie, having much practice, can catch an apple if she is standing under a tree from which one falls. While Bessie can walk between the two trees quickly (in much less than a minute), she can stand under only one tree at any time. Moreover, cows do not get a lot of exercise, so she is not willing to walk back and forth between the trees endlessly (and thus misses some apples).

Apples fall (one each minute) for T (1 <= T <= 1,000) minutes. Bessie is willing to walk back and forth at most W (1 <= W <= 30) times. Given which tree will drop an apple each minute, determine the maximum number of apples which Bessie can catch. Bessie starts at tree 1.

Input
* Line 1: Two space separated integers: T and W

* Lines 2..T+1: 1 or 2: the tree that will drop an apple each minute.

Output
* Line 1: The maximum number of apples Bessie can catch without walking more than W times.

Sample Input

7 2
2
1
1
2
2
1
1

Sample Output

6

Hint
INPUT DETAILS:

Seven apples fall - one from tree 2, then two in a row from tree 1, then two in a row from tree 2, then two in a row from tree 1. Bessie is willing to walk from one tree to the other twice.

OUTPUT DETAILS:

Bessie can catch six apples by staying under tree 1 until the first two have dropped, then moving to tree 2 for the next two, then returning back to tree 1 for the final two.
*/

#include <iostream>
#include <algorithm>
using namespace std;
 
int tree[1000];
int dp[1000][32][2]; // dp[x][y][z]表示第x + 1分的时候经过y次移动站在了z+1树下能吃到的最大苹果数
 
inline int move(const int &k)
{
	return k == 0 ? 1 : 0;
}
 
int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	int T, W;
	cin >> T >> W;
	for (int i = 0; i < T; ++i)
	{
		int t;
		cin >> t;
		tree[i] = t - 1;
	}
	if (tree[0] == 0)
	{
		dp[0][0][0] = 1;
	}
	else
	{
		dp[0][1][1] = 1;
	}
	for (int i = 0; i < T - 1; ++i)
	{
		for (int j = 0; j <= W; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				if (k == tree[i + 1])
				{
					// 下一个苹果掉在当前树下，那么下一分钟？
					// 站着不动吃一个
					dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k] + 1);
					// 移动没吃到，不变
					dp[i + 1][j + 1][move(k)] = max(dp[i + 1][j + 1][move(k)], dp[i][j][k]);
				}
				else
				{
					// 下一个苹果掉在另一树下，那么下一分钟？
					// 站着不动没吃到
					dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);
					// 移动吃一个
					dp[i + 1][j + 1][move(k)] = max(dp[i + 1][j + 1][move(k)], dp[i][j][k] + 1);
				}
			}
		}
	}
 
	cout << *max_element(dp[T - 1][0], dp[T - 1][0] + (W + 1) * 2) << endl;
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif
    return 0;
}