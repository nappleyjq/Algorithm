#ifndef ONLINE_JUDGE
#pragma warning(disable : 4996)
#endif
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
 
///////////////////////////SubMain//////////////////////////////////
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
