/*
Red and Black
Time Limit: 1000MS		Memory Limit: 30000K
Total Submissions: 38040		Accepted: 20641

Description
There is a rectangular room, covered with square tiles. Each tile is colored either red or black. A man is standing on a black tile. From a tile, he can move to one of four adjacent tiles. But he can't move on red tiles, he can move only on black tiles.

Write a program to count the number of black tiles which he can reach by repeating the moves described above.

Input
The input consists of multiple data sets. A data set starts with a line containing two positive integers W and H; W and H are the numbers of tiles in the x- and y- directions, respectively. W and H are not more than 20.

There are H more lines in the data set, each of which includes W characters. Each character represents the color of a tile as follows.

'.' - a black tile
'#' - a red tile
'@' - a man on a black tile(appears exactly once in a data set)
The end of the input is indicated by a line consisting of two zeros.

Output
For each data set, your program should output a line which contains the number of tiles he can reach from the initial tile (including itself).

Sample Input

6 9
....#.
.....#
......
......
......
......
......
#@...#
.#..#.
11 9
.#.........
.#.#######.
.#.#.....#.
.#.#.###.#.
.#.#..@#.#.
.#.#####.#.
.#.......#.
.#########.
...........
11 6
..#..#..#..
..#..#..#..
..#..#..###
..#..#..#@.
..#..#..#..
..#..#..#..
7 7
..#.#..
..#.#..
###.###
...@...
###.###
..#.#..
..#.#..
0 0

Sample Output

45
59
6
13

Source
Japan 2004 Domestic
*/

/*
Solution:
*/


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
 
#define MAX_W 20
#define MAX_H 20
char room[MAX_W][MAX_H];
int W, H;
const int direction[4][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1},
};
 
int step = 0;
 
int dfs(const int& x, const int& y)
{
	room[x][y] = '#';
	++step;
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + direction[i][0];
		int ny = y + direction[i][1];
		if (nx >= 0 && nx < W && ny >= 0 && ny < H && room[nx][ny] == '.')
		{
			dfs(nx, ny);
		}
	}
 
	return step;
}
 

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	while (cin >> W >> H, W > 0)
	{
		step = 0;
		int x, y;
		for (y = 0; y < H; ++y)
		{
			for (x = 0; x < W; ++x)
			{
				cin >> room[x][y];
			}
		}
 
		bool found = false;
		for (x = 0; x < W; ++x)
		{
			for (y = 0; y < H; ++y)
			{
				if (room[x][y] == '@')
				{
					found = true;
					break;
				}
			}
			if (found)
			{
				break;
			}
		}
 
		cout << dfs(x, y) << endl;
	}
#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	system("out.txt");
#endif
	return 0;
}
