/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0005

GCD and LCM
Write a program which computes the greatest common divisor (GCD) and the least common multiple (LCM) of given a and b.
Input

Input consists of several data sets. Each data set contains a and b separated by a single space in a line. The input terminates with EOF.
Constraints

    0 < a,b ≤ 2,000,000,000
    LCM(a,b) ≤ 2,000,000,000
    The number of data sets ≤ 50

Output

For each data set, print GCD and LCM separated by a single space in a line.
Sample Input

8 6
50000000 30000000

Output for the Sample Input

2 24
10000000 150000000
*/

#include <iostream>
using namespace std;
 
long long gcd(long long a, long long b)
{
	if (b == 0)return a;
	return gcd(b, a%b);
}
 
long long lcm(long long a, long long b)
{
	return a * b / gcd(a, b);
}
 

int main(int argc, char *argv[])
{
	long long a, b;
	while (cin >> a >> b)
	{
		cout << gcd(a, b) << " " << lcm(a, b) << endl;
	}
 
	return 0;
}
