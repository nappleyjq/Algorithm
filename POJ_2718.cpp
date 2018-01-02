/*
http://poj.org/problem?id=2718

Smallest Difference

Description
Given a number of distinct decimal digits, you can form one integer by choosing a non-empty subset of these digits and writing them in some order. The remaining digits can be written down in some order to form a second integer. Unless the resulting integer is 0, the integer may not start with the digit 0.

For example, if you are given the digits 0, 1, 2, 4, 6 and 7, you can write the pair of integers 10 and 2467. Of course, there are many ways to form such pairs of integers: 210 and 764, 204 and 176, etc. The absolute value of the difference between the integers in the last pair is 28, and it turns out that no other pair formed by the rules above can achieve a smaller difference.

Input
The first line of input contains the number of cases to follow. For each case, there is one line of input containing at least two but no more than 10 decimal digits. (The decimal digits are 0, 1, ..., 9.) No digit appears more than once in one line of the input. The digits will appear in increasing order, separated by exactly one blank space.

Output
For each test case, write on a single line the smallest absolute difference of two integers that can be written from the given digits as described by the rules above.

Sample Input

1
0 1 2 4 6 7

Sample Output

28
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
using namespace std;
 
int main(int argc, char *argv[])
{
	int n;
	cin >> n;
	cin.ignore();
	while (n--)
	{
		string all;
		getline(cin, all);
		all.erase(remove(all.begin(), all.end(), ' '), all.end());
		int length = all.size();
		int cut = length / 2;
		int permute = 1 << length;
		int result = 0x3F3F3F3F;
		do
		{
			bitset<10> used = static_cast<bitset<10>>(permute);
			string s1, s2;
			for (int i = 0; i < length; ++i)
			{
				if (used[i])
				{
					s1 += all[i];
				}
				else
				{
					s2 += all[i];
				}
			}
			if (s1.size() != cut)
			{
				continue;
			}
			if (s1[0] == '0' && s1.size() > 1)
			{
				continue;
			}
			// s1 s2 已经被切割出来了
			// 穷举它们
			do
			{
				int n1 = atoi(s1.c_str());
				do
				{
					if (s2[0] == '0' && s2.size() > 1)
					{
						continue;
					}
					int n2 = atoi(s2.c_str());
					int dif = abs(n1 - n2);
					//cout << s1 << ' ' << s2 << " dif " << dif << " result: " << result << endl;
					if (dif < result)
					{
						result = dif;
					}
				} while (next_permutation(s2.begin(), s2.end()));
			} while (next_permutation(s1.begin(), s1.end()));
		} while (--permute);
 
		cout << result << endl;
	}
	return 0;
}
