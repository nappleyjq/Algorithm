/*
http://poj.org/problem?id=3616

Milking Time

Description

Bessie is such a hard-working cow. In fact, she is so focused on maximizing her productivity that she decides to schedule her next N (1 ≤ N ≤ 1,000,000) hours (conveniently labeled 0..N-1) so that she produces as much milk as possible.

Farmer John has a list of M (1 ≤ M ≤ 1,000) possibly overlapping intervals in which he is available for milking. Each interval i has a starting hour (0 ≤ starting_houri ≤ N), an ending hour (starting_houri < ending_houri ≤ N), and a corresponding efficiency (1 ≤ efficiencyi ≤ 1,000,000) which indicates how many gallons of milk that he can get out of Bessie in that interval. Farmer John starts and stops milking at the beginning of the starting hour and ending hour, respectively. When being milked, Bessie must be milked through an entire interval.

Even Bessie has her limitations, though. After being milked during any interval, she must rest R (1 ≤ R ≤ N) hours before she can start milking again. Given Farmer Johns list of intervals, determine the maximum amount of milk that Bessie can produce in the N hours.

Input

* Line 1: Three space-separated integers: N, M, and R
* Lines 2..M+1: Line i+1 describes FJ's ith milking interval withthree space-separated integers: starting_houri , ending_houri , and efficiencyi

Output

* Line 1: The maximum number of gallons of milk that Bessie can product in the N hours

Sample Input

12 4 2
1 2 8
10 12 19
3 6 24
7 10 31

Sample Output

43
*/

#include <iostream>
#include <algorithm>
using namespace std;
 
struct Interval
{
	int starting_hour, ending_hour, efficiency;
	bool operator < (const Interval& i) const
	{
		return starting_hour < i.starting_hour;
	}
};
 
Interval interval[1024];
int dp[1024];
 
int main(int argc, char *argv[])
{
	int N, M, R;
	cin >> N >> M >> R;
	for (int i = 0; i < M; ++i)
	{
		cin >> interval[i].starting_hour >> interval[i].ending_hour >> interval[i].efficiency;
		// 实际的结束时间还需要加上休息时间
		interval[i].ending_hour += R;
	}
	sort(interval, interval + M);
	for (int i = 0; i < M; ++i)
	{
		dp[i] = interval[i].efficiency;
		for (int j = 0; j < i; ++j)
		{
			if (interval[j].ending_hour <= interval[i].starting_hour)
			{
				dp[i] = max(dp[i], dp[j] + interval[i].efficiency);
			}
		}
	}
 
	cout << *max_element(dp, dp + M) << endl;
    return 0;
}