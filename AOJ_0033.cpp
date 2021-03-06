/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0033

 図のように二股に分かれている容器があります。1 から 10 までの番号が付けられた10 個の玉を容器の開口部 A から落とし、左の筒 B か右の筒 C に玉を入れます。板 D は支点 E を中心に左右に回転できるので、板 D を動かすことで筒 B と筒 C のどちらに入れるか決めることができます。

開口部 A から落とす玉の並びを与えます。それらを順番に筒 B 又は筒 Cに入れていきます。このとき、筒 B と筒 C のおのおのが両方とも番号の小さい玉の上に大きい玉を並べられる場合は YES、並べられない場合は NO と出力するプログラムを作成してください。ただし、容器の中で玉の順序を入れ替えることはできないものとします。また、続けて同じ筒に入れることができるものとし、筒 B, C ともに 10 個の玉がすべて入るだけの余裕があるものとします。
Input

複数のデータセットが与えられます。１行目にデータセット数 N が与えられます。つづいて、N 行のデータセットが与えられます。各データセットに 10 個の番号が左から順番に空白区切りで与えられます。
Output

各データセットに対して、YES または NO を１行に出力して下さい。
Sample Input

2
3 1 4 2 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1

Output for the Sample Input

YES
NO
*/

#include <iostream>
#include <bitset>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
 
	int n;
	cin >> n;
	while (n--)
	{
		int ball[10];
		
		for (int i = 0; i < 10; ++i)
		{
			cin >> ball[i];
		}
 
		bitset<10> direction;
		int all = 1024;
		while (all-- > 0)
		{
			direction = static_cast<bitset<10> >(all);
			bool perfect = true;
			int left = 0;
			int right = 0;
			for (int i = 0; i < 10; ++i)
			{
				if (direction[i])
				{
					if (ball[i] > left)
					{
						left = ball[i];
					}
					else
					{
						perfect = false;
						break;
					}
				}
				else
				{
					if (ball[i] > right)
					{
						right = ball[i];
					}
					else
					{
						perfect = false;
						break;
					}
				}
			}
			if (perfect)
			{
				break;
			}
		}
	
		if (all >= 0)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
 
	return 0;
}
