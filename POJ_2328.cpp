/*
Radar Installation
Time Limit: 1000MS		Memory Limit: 10000K
Total Submissions: 94582		Accepted: 21070

Description
Assume the coasting is an infinite straight line. Land is in one side of coasting, sea in the other. Each small island is a point locating in the sea side. And any radar installation, locating on the coasting, can only cover d distance, so an island in the sea can be covered by a radius installation, if the distance between them is at most d.

We use Cartesian coordinate system, defining the coasting is the x-axis. The sea side is above x-axis, and the land side below. Given the position of each island in the sea, and given the distance of the coverage of the radar installation, your task is to write a program to find the minimal number of radar installations to cover all the islands. Note that the position of an island is represented by its x-y coordinates.

Figure A Sample Input of Radar Installations


Input
The input consists of several test cases. The first line of each case contains two integers n (1<=n<=1000) and d, where n is the number of islands in the sea and d is the distance of coverage of the radar installation. This is followed by n lines each containing two integers representing the coordinate of the position of each island. Then a blank line follows to separate the cases.

The input is terminated by a line containing pair of zeros

Output
For each test case output one line consisting of the test case number followed by the minimal number of radar installations needed. "-1" installation means no solution for that case.

Sample Input

3 2
1 2
-3 1
2 1

1 2
0 2

0 0

Sample Output

Case 1: 2
Case 2: 1
*/


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;
 
// 区间
struct Section
{
	double begin;
	double end;
	bool operator < (const Section& b) const 
	{  
		return begin < b.begin;
	} 
};
 

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	int n, d, __id;
	__id = 0;
	while(cin >> n >> d && n > 0)
	{
		int result = 0;
		vector<Section> s(n);
		for (int i = 0; i < n; ++i)
		{
			double x, y;
			cin >> x >> y;
			if (result == -1)
			{
				continue;
			}
			if (y > d)
			{
				// 如果y比半径大，一定不能覆盖
				result = -1;
				continue;
			}
			double r = sqrt(d * d - y * y);
			s[i].begin = x - r;
			s[i].end = x + r;
		}
 
		if (result == -1)
		{
			cout << "Case " << ++__id << ": " << result << endl;
			continue;
		}
 
		sort(s.begin(), s.end());
		double end = -numeric_limits<double>::max();
		for (vector<Section>::iterator it = s.begin(); it != s.end(); ++it)
		{
			// cout << it->begin << " " << it->end << endl;
			if (end < it->begin)
			{
				++result;
				end = it->end;
			}
			else if (end > it->end)
			{
				end = it->end;
			}
		}
 
		cout << "Case " << ++__id << ": " << result << endl;
	}
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif
    return 0;
}
