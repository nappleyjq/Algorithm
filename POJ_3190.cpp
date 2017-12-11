/*
Stall Reservations

Description
Oh those picky N (1 <= N <= 50,000) cows! They are so picky that each one will only be milked over some precise time interval A..B (1 <= A <= B <= 1,000,000), which includes both times A and B. Obviously, FJ must create a reservation system to determine which stall each cow can be assigned for her milking time. Of course, no cow will share such a private moment with other cows.

Help FJ by determining:

    The minimum number of stalls required in the barn so that each cow can have her private milking period
    An assignment of cows to these stalls over time

Many answers are correct for each test dataset; a program will grade your answer.

Input
Line 1: A single integer, N

Lines 2..N+1: Line i+1 describes cow i's milking interval with two space-separated integers.

Output
Line 1: The minimum number of stalls the barn must have.

Lines 2..N+1: Line i+1 describes the stall to which cow i will be assigned for her milking period.

Sample Input

5
1 10
2 4
3 6
5 8
4 7

Sample Output

4
1
2
3
2
4

Hint
Explanation of the sample:

Here's a graphical schedule for this output:

Time     1  2  3  4  5  6  7  8  9 10

Stall 1 c1>>>>>>>>>>>>>>>>>>>>>>>>>>>

Stall 2 .. c2>>>>>> c4>>>>>>>>> .. ..

Stall 3 .. .. c3>>>>>>>>> .. .. .. ..

Stall 4 .. .. .. c5>>>>>>>>> .. .. ..

Other outputs using the same number of stalls are possible.
*/


#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
 
struct Section
{
	unsigned int index;
	unsigned int begin;
	unsigned int end;
	bool operator < (const Section& b) const 
	{  
		return begin < b.begin;
	} 
};
 
struct Stall
{
	unsigned int id;
	unsigned int end;
	bool operator < (const Stall& b) const 
	{  
		return end > b.end;
	}
	Stall(){}
	Stall(unsigned int id, unsigned int end):id(id), end(end){}
};
 
#define MAX_COWS 50000
Section cow[MAX_COWS];
unsigned int result[MAX_COWS]; // 每头牛从属于哪个牛栏
priority_queue<Stall> que; // 最小堆，储存所有牛栏区间的结束点（也就是最右端）
 
inline void put_cow(const int& i, const bool& new_stall)
{
	Stall s;
	if (new_stall)
	{
		s.id = que.size() + 1;
	}
	else
	{
		s.id = que.top().id; que.pop();
	}
	s.end = cow[i].end;
	result[cow[i].index] = s.id;
	que.push(s);
}
 

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	int N;
	cin >> N;
 
	for (int i = 0; i < N; ++i)
	{
		cow[i].index = i;
		cin >> cow[i].begin;
		cin >> cow[i].end;
	}
 
	sort(cow, cow + N);
	put_cow(0, true);
 
	for (int i = 1; i < N; ++i)
	{
		put_cow (i, cow[i].begin <= que.top().end);
	}
 
	cout << que.size() << endl;
	for (int i = 0; i < N; ++i)
	{
		cout << result[i] << endl;
	}
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif
    return 0;
}
