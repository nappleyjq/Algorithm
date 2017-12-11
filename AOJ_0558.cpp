/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0558

チーズ (Cheese)
問題

今年も JOI 町のチーズ工場がチーズの生産を始め，ねずみが巣から顔を出した．JOI 町は東西南北に区画整理されていて，各区画は巣，チーズ工場，障害物，空き地のいずれかである．ねずみは巣から出発して全てのチーズ工場を訪れチーズを 1 個ずつ食べる．

この町には，N 個のチーズ工場があり，どの工場も１種類のチーズだけを生産している．チーズの硬さは工場によって異なっており，硬さ 1 から N までのチーズを生産するチーズ工場がちょうど 1 つずつある．

ねずみの最初の体力は 1 であり，チーズを 1 個食べるごとに体力が 1 増える．ただし，ねずみは自分の体力よりも硬いチーズを食べることはできない．

ねずみは，東西南北に隣り合う区画に 1 分で移動することができるが，障害物の区画には入ることができない．チーズ工場をチーズを食べずに通り過ぎることもできる．すべてのチーズを食べ終えるまでにかかる最短時間を求めるプログラムを書け．ただし，ねずみがチーズを食べるのにかかる時間は無視できる．
入力

入力は H+1 行ある．1 行目には 3 つの整数 H，W，N (1 ≤ H ≤ 1000，1 ≤ W ≤ 1000，1 ≤ N ≤ 9) がこの順に空白で区切られて書かれている．2 行目から H+1 行目までの各行には，'S'，'1', '2', ..., '9'，'X'，'.' からなる W 文字の文字列が書かれており，各々が各区画の状態を表している．北から i 番目，西から j 番目の区画を (i,j) と記述することにすると (1 ≤ i ≤ H, 1 ≤ j ≤ W)，第 i+1 行目の j 番目の文字は，区画 (i,j) が巣である場合は 'S' となり，障害物である場合は 'X' となり，空き地である場合は '.' となり，硬さ 1, 2, ..., 9 のチーズを生産する工場である場合はそれぞれ '1', '2', ..., '9' となる．入力には巣と硬さ 1, 2, ..., N のチーズを生産する工場がそれぞれ 1 つずつある．他のマスは障害物または空き地であることが保証されている．ねずみは全てのチーズを食べられることが保証されている．
出力

すべてのチーズを食べ終えるまでにかかる最短時間（分）を表す整数を 1 行で出力せよ．
入出力例
入力例 1

3 3 1
S..
...
..1

出力例 1

4

入力例 2

4 5 2
.X..1
....X
.XX.S
.2.X.

出力例 2

12

入力例 3

10 10 9
.X...X.S.X
6..5X..X1X
...XXXX..X
X..9X...X.
8.X2X..X3X
...XX.X4..
XX....7X..
X..X..XX..
X...X.XX..
..X.......

出力例 3

91
*/

/*
Solution:breadth first search
*/

#include <iostream>
#include <queue>
using namespace std;
int w, h, n;
char map[1024][1024];
// 各点到当前工厂的距离
int d[1024][1024];
const int direction[4][2] = {
	{ -1, 0 },
	{ 1, 0 },
	{ 0, -1 },
	{ 0, 1 },
};
 
int factory[16][2];
typedef pair<int, int> P;
 
 
 
//************************************
// Method:    bfs
// FullName:  bfs
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: const int & sx 起点x
// Parameter: const int & sy 起点y
// Parameter: const int & gx 终点x
// Parameter: const int & gy 终点y
//************************************
int bfs(const int& sx, const int& sy, const int& gx, const int& gy)
{
	//memset(d, -1, sizeof(d));
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			d[j][i] = -1;
		}
	}
	queue<P> que;
	que.push(P(sx, sy));
	d[sx][sy] = 0;
	while (que.size())
	{
		const P p = que.front(); que.pop();
		// 如果是终点就结束
		if (p.first == gx && p.second == gy)
		{
			break;
		}
 
		// 四方向漫游
		for (int i = 0; i < 4; ++i)
		{
			int nx = p.first + direction[i][0];
			int ny = p.second + direction[i][1];
			// 是否可以移动，并且该点没有访问过
			if (0 <= nx && nx < w && 0 <= ny && ny < h && map[nx][ny] != 'X' && d[nx][ny] == -1)
			{
				que.push(P(nx, ny));
				d[nx][ny] = d[p.first][p.second] + 1;
			}
		}
	}
 
	return d[gx][gy];
}
 

int main(int argc, char *argv[])
{
 
	cin >> h >> w >> n;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			cin >> map[j][i];
		}
	}
 
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (map[j][i] == 'S')
			{
				factory[0][0] = j;
				factory[0][1] = i;
				map[j][i] = '.';
			}
			else if (isdigit(map[j][i]))
			{
				int index = map[j][i] - '0';
				factory[index][0] = j;
				factory[index][1] = i;
			}
		}
	}
 
	int step = 0;
	for (int i = 0; i < n; ++i)
	{
		// 按顺序吃遍中华
		step += bfs(factory[i][0], factory[i][1], factory[i + 1][0], factory[i + 1][1]);
	}
	
	cout << step << endl;
 
	return 0;
}
