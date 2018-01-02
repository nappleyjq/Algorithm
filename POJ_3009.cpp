/*
http://poj.org/problem?id=3009

Description

On Planet MM-21, after their Olympic games this year, curling is getting popular. But the rules are somewhat different from ours. The game is played on an ice game board on which a square mesh is marked. They use only a single stone. The purpose of the game is to lead the stone from the start to the goal with the minimum number of moves.

Fig. 1 shows an example of a game board. Some squares may be occupied with blocks. There are two special squares namely the start and the goal, which are not occupied with blocks. (These two squares are distinct.) Once the stone begins to move, it will proceed until it hits a block. In order to bring the stone to the goal, you may have to stop the stone by hitting it against a block, and throw again.


Fig. 1: Example of board (S: start, G: goal)

The movement of the stone obeys the following rules:

    At the beginning, the stone stands still at the start square.
    The movements of the stone are restricted to x and y directions. Diagonal moves are prohibited.
    When the stone stands still, you can make it moving by throwing it. You may throw it to any direction unless it is blocked immediately(Fig. 2(a)).
    Once thrown, the stone keeps moving to the same direction until one of the following occurs:
        The stone hits a block (Fig. 2(b), (c)).
            The stone stops at the square next to the block it hit.
            The block disappears. 
        The stone gets out of the board.
            The game ends in failure. 
        The stone reaches the goal square.
            The stone stops there and the game ends in success. 
    You cannot throw the stone more than 10 times in a game. If the stone does not reach the goal in 10 moves, the game ends in failure.


Fig. 2: Stone movements

Under the rules, we would like to know whether the stone at the start can reach the goal and, if yes, the minimum number of moves required.

With the initial configuration shown in Fig. 1, 4 moves are required to bring the stone from the start to the goal. The route is shown in Fig. 3(a). Notice when the stone reaches the goal, the board configuration has changed as in Fig. 3(b).


Fig. 3: The solution for Fig. D-1 and the final board configuration

Input

The input is a sequence of datasets. The end of the input is indicated by a line containing two zeros separated by a space. The number of datasets never exceeds 100.

Each dataset is formatted as follows.

    the width(=w) and the height(=h) of the board
    First row of the board
    ...
    h-th row of the board

The width and the height of the board satisfy: 2 <= w <= 20, 1 <= h <= 20.

Each line consists of w decimal numbers delimited by a space. The number describes the status of the corresponding square.

    0 	vacant square
    1 	block
    2 	start position
    3 	goal position

The dataset for Fig. D-1 is as follows:

    6 6
    1 0 0 2 1 0
    1 1 0 0 0 0
    0 0 0 0 0 3
    0 0 0 0 0 0
    1 0 0 0 0 1
    0 1 1 1 1 1

Output

For each dataset, print a line having a decimal integer indicating the minimum number of moves along a route from the start to the goal. If there are no such routes, print -1 instead. Each line should not have any character other than this number.

Sample Input

2 1
3 2
6 6
1 0 0 2 1 0
1 1 0 0 0 0
0 0 0 0 0 3
0 0 0 0 0 0
1 0 0 0 0 1
0 1 1 1 1 1
6 1
1 1 2 1 1 3
6 1
1 0 2 1 1 3
12 1
2 0 1 1 1 1 1 1 1 1 1 3
13 1
2 0 1 1 1 1 1 1 1 1 1 1 3
0 0

Sample Output

1
4
-1
4
10
-1
*/

/*
Solution:depth first search
*/

#ifndef ONLINE_JUDGE
#pragma warning(disable : 4996)
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int w, h;
int map[32][32];
int sx, sy;
int min_step;
const int direction[4][2] = {
	{ -1, 0 },
	{ 1, 0 },
	{ 0, -1 },
	{ 0, 1 },
};
 
void dfs(const int& x, const int& y, int step)
{
	if (step >= 10 || step > min_step)
	{
		return;
	}
	
	for (int i = 0; i < 4; ++i)
	{
		int nx = x;
		int ny = y;
		// 让石头往固定的方向一直飞
		while(nx >= 0 && nx < w && ny >= 0 && ny < h)
		{
			switch (map[nx][ny])
			{
				case 0:
				{
				    // 继续飞
					nx += direction[i][0];
					ny += direction[i][1];
				}break;
				case 3:
				{
					// 到家了
					if (step + 1 < min_step)
					{
						min_step = step + 1;
					}
					nx = -1;
				}break;
				case 1:
				{
 
					// 撞到了block
					if (!(nx - direction[i][0] == x && ny - direction[i][1] == y))
					{
						// 中间有空地，不是紧挨着block
						// 石头消失
						map[nx][ny] = 0;
						// 后退一步扔石头
						dfs(nx - direction[i][0], ny - direction[i][1], step + 1);
						// 复原地图，供下一个方向尝试
						map[nx][ny] = 1;
					}
					// 开始下一个方向
					nx = -1;
				}break;
				default:
					break;
			}
		}
		
	}
}
 
int main(int argc, char *argv[])
{
	while (cin >> w >> h, w != 0)
	{
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
				if (2 == map[j][i])
				{
					sx = j;
					sy = i;
					i = h;
					break;
				}
			}
		}
 
		map[sx][sy] = 0;
		min_step = 11;
		dfs(sx, sy, 0);
		if (min_step > 10)
		{
			min_step = -1;
		}
		cout << min_step << endl;
	}
	return 0;
}
