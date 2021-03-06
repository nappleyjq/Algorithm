/*
http://www.hankcs.com/program/cpp/poj-1862-stripies.html

Stripies

Description
Our chemical biologists have invented a new very useful form of life called stripies (in fact, they were first called in Russian - polosatiki, but the scientists had to invent an English name to apply for an international patent). The stripies are transparent amorphous amebiform creatures that live in flat colonies in a jelly-like nutrient medium. Most of the time the stripies are moving. When two of them collide a new stripie appears instead of them. Long observations made by our scientists enabled them to establish that the weight of the new stripie isn't equal to the sum of weights of two disappeared stripies that collided; nevertheless, they soon learned that when two stripies of weights m1 and m2 collide the weight of resulting stripie equals to 2*sqrt(m1*m2). Our chemical biologists are very anxious to know to what limits can decrease the total weight of a given colony of stripies.
You are to write a program that will help them to answer this question. You may assume that 3 or more stipies never collide together.

Input
The first line of the input contains one integer N (1 <= N <= 100) - the number of stripies in a colony. Each of next N lines contains one integer ranging from 1 to 10000 - the weight of the corresponding stripie.

Output
The output must contain one line with the minimal possible total weight of colony with the accuracy of three decimal digits after the point.

Sample Input

3
72
30
50

Sample Output

120.000
*/

#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
	int N;
	cin >> N;
	priority_queue<double> que;
	for (int i = 0; i < N; ++i)
	{
		double l;
		cin >> l;
		que.push(l);
	}
	while(que.size() != 1)
	{
		double a = que.top(); que.pop();
		double b = que.top(); que.pop();
		que.push(2 * sqrt(a * b));
	}
	cout.setf(ios::fixed);
	cout.precision(3);
	cout << que.top() << endl;
    return 0;
}
