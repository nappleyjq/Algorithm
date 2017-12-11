/*
Solution:Use greedy algorithm to choose the interval as longer as possible from left to right. 

The first step is to sort cows according to the time and then update:start_point=end_point+1. Then search the left cows to choose the one that can both cover the start_point and the farest end_point and then update end_point. 
*/


/*
Cleaning Shifts

Description
Farmer John is assigning some of his N (1 <= N <= 25,000) cows to do some cleaning chores around the barn. He always wants to have one cow working on cleaning things up and has divided the day into T shifts (1 <= T <= 1,000,000), the first being shift 1 and the last being shift T.

Each cow is only available at some interval of times during the day for work on cleaning. Any cow that is selected for cleaning duty will work for the entirety of her interval.

Your job is to help Farmer John assign some cows to shifts so that (i) every shift has at least one cow assigned to it, and (ii) as few cows as possible are involved in cleaning. If it is not possible to assign a cow to each shift, print -1.

Input
* Line 1: Two space-separated integers: N and T

* Lines 2..N+1: Each line contains the start and end times of the interval during which a cow can work. A cow starts work at the start time and finishes after the end time.

Output
* Line 1: The minimum number of cows Farmer John needs to hire or -1 if it is not possible to assign a cow to each shift.

Sample Input

3 10
1 7
3 6
6 10

Sample Output

2

Hint
This problem has huge input data,use scanf() instead of cin to read data to avoid time limit exceed.

INPUT DETAILS:

There are 3 cows and 10 shifts. Cow #1 can work shifts 1..7, cow #2 can work shifts 3..6, and cow #3 can work shifts 6..10.

OUTPUT DETAILS:

By selecting cows #1 and #3, all shifts are covered. There is no way to cover all the shifts using fewer than 2 cows.
*/

#include <iostream>
#include <algorithm>
using namespace std;
int N, T;
 
struct Cow
{
	int begin;	// 开始时间 
	int end;	// 结束时间 
};
 
#define MAX_COWS 25000
Cow cow[MAX_COWS];
 
bool is_greater(const Cow& a, const Cow& b)
{
	return a.begin < b.begin || (a.begin == b.begin && a.end > b.end);
}
 
int solve()
{
	int used_cows = 0;
	int end = 0;
	int index = 0;
	while(end < T)
	{
		int begin = end + 1;
		// 寻找一头既能从begin干起，又能一直干到最远的牛 
		for (int i = index; i < N; ++i)
		{
			if (cow[i].begin <= begin)
			{
				// 能够覆盖起始点 
				if (cow[i].end >= begin)
				{
					// 将终点延长到最远 
					end = max(end, cow[i].end);
				}
			}
			else
			{
				// 不能覆盖起始点，说明上一头牛的终点就是最远点，需要换一头牛了 
				index = i;
				break;
			}
		}
 
		// 没找到这样的牛，这个case失败 
		if (begin > end)
		{
			return -1;
		}
		else
		{
			++used_cows;
		}
	}
 
	return used_cows;
}
 
int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	cin >> N >> T;
	for (int i = 0; i < N; ++i)
	{
		cin >> cow[i].begin >> cow[i].end;
	}
	sort(cow, cow + N, is_greater);
	cout << solve() << endl;
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif
    return 0;
}
