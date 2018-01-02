/*
http://poj.org/problem?id=1742

Coins

Description
People in Silverland use coins.They have coins of value A1,A2,A3...An Silverland dollar.One day Tony opened his money-box and found there were some coins.He decided to buy a very nice watch in a nearby shop. He wanted to pay the exact price(without change) and he known the price would not more than m.But he didn't know the exact price of the watch.
You are to write a program which reads n,m,A1,A2,A3...An and C1,C2,C3...Cn corresponding to the number of Tony's coins of value A1,A2,A3...An then calculate how many prices(form 1 to m) Tony can pay use these coins.

Input
The input contains several test cases. The first line of each test case contains two integers n(1<=n<=100),m(m<=100000).The second line contains 2n integers, denoting A1,A2,A3...An,C1,C2,C3...Cn (1<=Ai<=100000,1<=Ci<=1000). The last test case is followed by two zeros.

Output
For each test case output the answer on a single line.

Sample Input

3 10
1 2 4 2 1 1
2 5
1 4 2 1
0 0

Sample Output

8
4
*/

#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
 
int dp[100000 + 16]; // dp[i][j] := 用前i种硬币凑成j时第i种硬币最多能剩余多少个
int A[100 + 16];
int C[100 + 16];

int main(int argc, char *argv[])
{
	int n, m;
	while(cin >> n >> m && n > 0)
	{
		memset(dp, -1, sizeof(dp));
		dp[0] = 0;
		for (int i = 0; i < n; ++i)
		{
			cin >> A[i];
		}
		for (int i = 0; i < n; ++i)
		{
			cin >> C[i];
		}
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j <= m; ++j)
			{
				if (dp[j] >= 0)
				{
					dp[j] = C[i];
				}
				else if (j < A[i]						// 用一个就超出，不能用
						|| dp[j - A[i]] <= 0)		// 连凑比j小的数的时候都用完了，此时更加用完了
				{
					dp[j] = -1;
				}
				else
				{
					dp[j] = dp[j - A[i]] - 1;		// 用上了一个第i个硬币
				}
			}
		}
		int answer = count_if(dp + 1, dp + 1 + m , bind2nd(greater_equal<int>(), 0)); // 总额0不算在答案内
		cout << answer << endl;
	}
    return 0;
}
