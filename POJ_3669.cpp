/*
http://poj.org/problem?id=3669

Meteor Shower

Description

Bessie hears that an extraordinary meteor shower is coming; reports say that these meteors will crash into earth and destroy anything they hit. Anxious for her safety, she vows to find her way to a safe location (one that is never destroyed by a meteor) . She is currently grazing at the origin in the coordinate plane and wants to move to a new, safer location while avoiding being destroyed by meteors along her way.

The reports say that M meteors (1 ≤ M ≤ 50,000) will strike, with meteor i will striking point (Xi, Yi) (0 ≤ Xi ≤ 300; 0 ≤ Yi ≤ 300) at time Ti (0 ≤ Ti  ≤ 1,000). Each meteor destroys the point that it strikes and also the four rectilinearly adjacent lattice points.

Bessie leaves the origin at time 0 and can travel in the first quadrant and parallel to the axes at the rate of one distance unit per second to any of the (often 4) adjacent rectilinear points that are not yet destroyed by a meteor. She cannot be located on a point at any time greater than or equal to the time it is destroyed).

Determine the minimum time it takes Bessie to get to a safe place.

Input

* Line 1: A single integer: M
* Lines 2..M+1: Line i+1 contains three space-separated integers: Xi, Yi, and Ti

Output

* Line 1: The minimum time it takes Bessie to get to a safe place or -1 if it is impossible.

Sample Input

4
0 0 2
2 1 2
1 1 2
0 3 5

Sample Output

5
*/

/*
Solution:breadth first search
*/

#ifndef ONLINE_JUDGE
#pragma warning(disable : 4996)
#endif
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
 
#define INDEX_MAX 512
int map[INDEX_MAX][INDEX_MAX];
bool visited[INDEX_MAX][INDEX_MAX];
struct Meteor
{
	int x, y, t;
};
typedef Meteor P;
 
Meteor m[50008];
int n;
 
const int direction[5][2] = {
	{ -1, 0 },
	{ 1, 0 },
	{ 0, -1 },
	{ 0, 1 },
	{ 0, 0 },
};
 
int last;
 
int bfs()
{
	memset(visited, 0, sizeof(visited));
	queue<P> que;
	P current;
	current.x = 0;
	current.y = 0;
	// 当前花费时间
	current.t = 0;
	que.push(current);
	while (que.size())
	{
		// 做个备份
		const P p = que.front(); que.pop();
		for (int j = 0; j < 4; ++j)
		{
			current = p;
			current.x = current.x + direction[j][0];
			current.y = current.y + direction[j][1];
			++current.t;
			
			if (current.x >= 0 && current.y >= 0 && map[current.x][current.y] > current.t && !visited[current.x][current.y])
			{
				visited[current.x][current.y] = true;
				// 爆炸时间大于当前时间，是安全的
				if (map[current.x][current.y] > last)
				{
					// 当前位置爆炸时间大于流星雨最晚落下的时间，说明跑出了流星雨区域
					return current.t;
				}
				que.push(current);
			}
		}
	}
 
	return -1;
}
 

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> m[i].x >> m[i].y >> m[i].t;
	}
	
	// 地图中每个点的值表示最早在什么时候被炸毁
	memset(map, 0x7F, sizeof(map));
	for (int i = 0; i < n; ++i)
	{
		last = max(last, m[i].t);
		for (int j = 0; j < 5; ++j)
		{
			int nx = m[i].x + direction[j][0];
			int ny = m[i].y + direction[j][1];
			if (nx >= 0 && ny >= 0 && map[nx][ny] > m[i].t)
			{
				map[nx][ny] = m[i].t;
			}
		}
	}
	if (map[0][0] == 0)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << bfs() << endl;
	}
#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	system("out.txt");
#endif
	return 0;
}
