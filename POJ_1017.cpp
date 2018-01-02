/*
http://poj.org/problem?id=1017

Packets

Description
A factory produces products packed in square packets of the same height h and of the sizes 1*1, 2*2, 3*3, 4*4, 5*5, 6*6. These products are always delivered to customers in the square parcels of the same height h as the products have and of the size 6*6. Because of the expenses it is the interest of the factory as well as of the customer to minimize the number of parcels necessary to deliver the ordered products from the factory to the customer. A good program solving the problem of finding the minimal number of parcels necessary to deliver the given products according to an order would save a lot of money. You are asked to make such a program.

Input
The input file consists of several lines specifying orders. Each line specifies one order. Orders are described by six integers separated by one space representing successively the number of packets of individual size from the smallest size 1*1 to the biggest size 6*6. The end of the input file is indicated by the line containing six zeros.

Output
The output file contains one line for each line in the input file. This line contains the minimal number of parcels into which the order from the corresponding line of the input file can be packed. There is no line in the output file corresponding to the last ``null'' line of the input file.

Sample Input

0 0 4 0 0 1 
7 5 1 0 0 0 
0 0 0 0 0 0 

Sample Output

2 
1 
*/

#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
	int n, p1, p2, p3, p4, p5, p6, x , y;
	int space[4] = {0, 5, 3, 1}; // 一个箱子放入几个 3 * 3 后留下的缝隙可以放入几个 2 * 2
	while(true)
	{
		cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
		if(p1 == 0 && p2 == 0 && p3 == 0 && p4 == 0 && p5 == 0 && p6 == 0)
		{
			break;
		}
		// 第一次放“放不下第二个该型号”的型号，需要消耗n个箱子
		n = p4 + p5 + p6 + ceil(p3 / 4.0); // 对 3 * 3 的 package 来讲，四个刚好，否则向上取整
		// 计算 4 * 4 的型号和 3 * 3 的型号之间的缝隙可以放下多少个 2 * 2 的型号
		y = 5 * p4 + space[p3 % 4];
		// 2 * 2 的型号填入这些缝隙，如果填不下，再多消耗几个箱子
		if(p2 > y)
		{
			n += ceil((p2 - y) / 9.0); // 多出来的每9个刚好一个箱子
		}
		// 计算现在空了多少个 1 * 1 的位置
		x = 36 * n - 36 * p6 - 25 * p5 - 16 * p4 - 9 * p3 - 4 * p2;
		// 1 * 1 的型号填入这些缝隙，如果填不下，再多消耗几个箱子
		if(p1>x)
		{
			n += ceil((p1 - x) / 36.0);
		}
		cout << n << endl;
	}
    return 0;
}
