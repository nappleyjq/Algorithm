/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0121

Seven Puzzle
Time Limit : 1 sec, Memory Limit : 65536 KB
7 パズル

7 パズルは 8 つの正方形のカードとこれらのカードがぴたりと収まる枠で構成されています。それぞれのカードには、互いに区別できるように 0, 1, 2, ..., 7 と番号がつけられています。枠には、縦に 2 個、横に 4 個のカードを並べることができます。

7 パズルを始めるときには、まず枠にすべてのカードを入れます。枠のなかで 0 のカードだけは、上下左右に隣接するカードと位置を交換することができます。たとえば、枠の状態が図(a) のときに、0 のカードの右に隣接した、7 のカードと位置を交換すれば、図(b) の状態になります。あるいは、図(a) の状態から 0 のカードの下に隣接した 2 のカードと位置を交換すれば図(c) の状態になります。図(a) の状態で 0 のカードと上下左右に隣接するカードは 7 と 2 のカードだけなので、これ以外の位置の入れ替えは許されません。

ゲームの目的は、カードをきれいに整列して図(d) の状態にすることです。最初の状態を入力とし、カードをきれいに整列するまでに、必要な最小手数を出力するプログラムを作成してください。ただし、入力されたカードの状態からは図(d) の状態に移ることは可能であるとします。

入力データは、1 行に 8 つの数字が空白区切りで与えられます。これらは、最初の状態のカードの並びを表します。例えば、図(a) の数字表現は0 7 3 4 2 5 1 6 に、図(c) は 2 7 3 4 0 5 1 6 となります。
	
図(a) 0 7 3 4 2 5 1 6 の場合 	図(b) 7 0 3 4 2 5 1 6 の場合


	
図(c) 2 7 3 4 0 5 1 6 の場合 	図(d) 0 1 2 3 4 5 6 7 (最終状態)

Input

上記形式で複数のパズルが与えられます。入力の最後まで処理してください。 与えられるパズルの数は 1,000 以下です。
Output

各パズルについて、最終状態へ移行する最小手数を１行に出力してください。
Sample Input

0 1 2 3 4 5 6 7
1 0 2 3 4 5 6 7
7 6 5 4 3 2 1 0

Output for the Sample Input

0
1
28

*/

/*
Solution:breadth first search
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
 
map<string, int> dp;
int direction[4] = { 1, -1, 4, -4 };
 
//************************************
// Method:    bfs
// FullName:  bfs
// Access:    public 
// Returns:   void
// Qualifier: 让0漫游整个字串
//************************************
void bfs()
{
	queue<string> que;
	que.push("01234567");
	dp["01234567"] = 0;
	while (!que.empty())
	{
		string now = que.front(); que.pop();
		// p是'0'的位置
		int p = 0;
		for (int j = 0; j < 8; ++j)
		{
			if (now[j] == '0')
			{
				p = j;
				break;
			}
		}
 
		for (int i = 0; i < 4; ++i)
		{
			int n = p + direction[i];
			if (0 <= n && n < 8 && 
				!(p == 3 && i == 0) && // 右上角不能再往右了
				!(p == 4 && i == 1))   // 左下角不能再往左了
			{
				string next = now;
				swap(next[p], next[n]);
				if (dp.find(next) == dp.end())
				{
					dp[next] = dp[now] + 1;
					que.push(next);
				}
			}
		}
	}
}
 

int main(int argc, char *argv[])
{
 
	bfs();
	string line;
	while (getline(cin, line))
	{
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		cout << dp[line] << endl;
	}
 
	return 0;
}
