/*
http://poj.org/problem?id=3187

Backward Digit Sums
Time Limit: 1000MS		Memory Limit: 65536K
Total Submissions: 8081		Accepted: 4631

Description
FJ and his cows enjoy playing a mental game. They write down the numbers from 1 to N (1 <= N <= 10) in a certain order and then sum adjacent numbers to produce a new list with one fewer number. They repeat this until only a single number is left. For example, one instance of the game (when N=4) might go like this:

    3   1   2   4

      4   3   6

        7   9

         16

Behind FJ's back, the cows have started playing a more difficult game, in which they try to determine the starting sequence from only the final total and the number N. Unfortunately, the game is a bit above FJ's mental arithmetic capabilities.

Write a program to help FJ play the game and keep up with the cows.

Input
Line 1: Two space-separated integers: N and the final sum.

Output
Line 1: An ordering of the integers 1..N that leads to the given sum. If there are multiple solutions, choose the one that is lexicographically least, i.e., that puts smaller numbers first.

Sample Input

4 16

Sample Output

3 1 2 4

Hint
Explanation of the sample:

There are other possible sequences, such as 3 2 1 4, but 3 1 2 4 is the lexicographically smallest.
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int c(int n, int k)
{
	int result = 1;
	for (int i = 0; i < k; ++i)
	{
		result = result * (n - i) / (i + 1);
	}
 
	return result;
}
int main(int argc, char *argv[])
{
	int N, Sum;
	cin >> N >> Sum;
	int line[16];
	int i = 0;
	for (; i < N; ++i)
	{
		line[i] = i + 1;
	}
	do 
	{
		int result = 0;
		for (i = 0; i < N; ++i)
		{
			result += c(N - 1, i) * line[i];
		}
		if (result == Sum)
		{
			break;
		}
	} while (next_permutation(line, line + N));
	copy(line, line + N, ostream_iterator<int>(cout, " "));
    return 0;
}
    
