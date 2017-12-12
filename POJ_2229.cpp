/*
http://poj.org/problem?id=2229

Sumsets

Description
Farmer John commanded his cows to search for different sets of numbers that sum to a given number. The cows use only numbers that are an integer power of 2. Here are the possible sets of numbers that sum to 7:

1) 1+1+1+1+1+1+1
2) 1+1+1+1+1+2
3) 1+1+1+2+2
4) 1+1+1+4
5) 1+2+2+2
6) 1+2+4

Help FJ count all possible representations for a given integer N (1 <= N <= 1,000,000).

Input
A single line with a single integer, N.

Output
The number of ways to represent N as the indicated sum. Due to the potential huge size of this number, print only last 9 digits (in base 10 representation).

Sample Input

7

Sample Output

6
*/

#include <iostream>
using namespace std;
 
int dp[1000000 + 1]; // 数字i的分解数
 
int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	int N;
	cin >> N;
	dp[0] = 1; // 2^0
	for (int i = 1; i <= N; ++i)
	{
		if ((i & 0x1) == 0)
		{
			dp[i] = dp[ i / 2]; // 将i / 2的每个构成数乘以2，得到i
		}
		dp[i] += dp[i - 1]; // 将i - 1的构成数拿过来加一
		dp[i] %= 1000000000;
	}
	cout << dp[N] << endl;
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif
    return 0;
}