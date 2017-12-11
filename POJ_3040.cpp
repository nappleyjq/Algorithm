/*
http://poj.org/problem?id=3040

Allowance

Description
As a reward for record milk production, Farmer John has decided to start paying Bessie the cow a small weekly allowance. FJ has a set of coins in N (1 <= N <= 20) different denominations, where each denomination of coin evenly divides the next-larger denomination (e.g., 1 cent coins, 5 cent coins, 10 cent coins, and 50 cent coins).Using the given set of coins, he would like to pay Bessie at least some given amount of money C (1 <= C <= 100,000,000) every week.Please help him ompute the maximum number of weeks he can pay Bessie.

Input
* Line 1: Two space-separated integers: N and C

* Lines 2..N+1: Each line corresponds to a denomination of coin and contains two integers: the value V (1 <= V <= 100,000,000) of the denomination, and the number of coins B (1 <= B <= 1,000,000) of this denomation in Farmer John's possession.

Output
* Line 1: A single integer that is the number of weeks Farmer John can pay Bessie at least C allowance

Sample Input

3 6
10 1
1 100
5 120

Sample Output

111

Hint
INPUT DETAILS:
FJ would like to pay Bessie 6 cents per week. He has 100 1-cent coins,120 5-cent coins, and 1 10-cent coin.

OUTPUT DETAILS:
FJ can overpay Bessie with the one 10-cent coin for 1 week, then pay Bessie two 5-cent coins for 10 weeks and then pay Bessie one 1-cent coin and one 5-cent coin for 100 weeks.
*/

#include <iostream>
#include <functional>
#include <algorithm>
#include <limits>
using namespace std;
 
typedef pair<int, int> Coin;	// 硬币 面值和数量
Coin coin[20];
int need[20];

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	int N, C;
	cin >> N >> C;
	for (int i = 0; i < N; ++i)
	{
		cin >> coin[i].first >> coin[i].second;
	}
	int week = 0;
	// 面额不小于C的一定可以支付一周
	for (int i = 0; i < N; ++i)
	{
		if (coin[i].first >= C)
		{
			week += coin[i].second;
			coin[i].second = 0;
		}
	}
	sort(coin, coin + N, greater<Coin>());
	while(true)
	{
		int sum = C; // 等待凑足的sum
		memset(need, 0, sizeof(need));
		// 从大到小
		for (int i = 0; i < N; ++i)
		{
			if (sum > 0 && coin[i].second > 0)
			{
				int can_use = min(coin[i].second, 
								  sum / coin[i].first);
				if (can_use > 0)
				{
					sum -= can_use * coin[i].first;
					need[i] = can_use;
				}
			}
		}
		// 从小到大
		for (int i = N - 1; i >= 0; --i)
		{
			if (sum > 0 && coin[i].second > 0)
			{
				int can_use = min(coin[i].second - need[i],                   // 上个loop用掉了一些
								  (sum + coin[i].first - 1) / coin[i].first); // 允许多出不超过一个面值的金额
				if (can_use > 0)
				{
					sum -= can_use * coin[i].first;
					need[i] += can_use;
				}
			}
		}
 
		if(sum > 0)
		{
			break;
		}
 
		int add_up = numeric_limits<int>::max(); // 凑起来的week数
		// add_up多少个最优的week 受限于 每种面值能满足最优解下的需求个数多少次
		for (int i = 0; i < N; ++i)
		{
			if (need[i] == 0)
			{
				continue;
			}
			add_up = min(add_up, coin[i].second / need[i]);
		}
		week += add_up;
		// 最优解生效，更新剩余硬币数量
		for (int i = 0; i < N; ++i)
		{
			if (need[i] == 0)
			{
				continue;
			}
			coin[i].second -= add_up * need[i];
		}
	}
	cout << week << endl;
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif
    return 0;
}
