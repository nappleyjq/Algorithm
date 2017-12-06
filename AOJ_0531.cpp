#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include <cstring>
#define MAX_N 1000 + 16
 
using namespace std;
 
int N, H, W;
int X1[MAX_N], X2[MAX_N], Y1[MAX_N], Y2[MAX_N];
int fld[2 * MAX_N][2 * MAX_N], // 填充遍历用，代表坐标(i, j)处是否空白（压缩后）
dx[4] = { 1, -1, 0, 0 }, dy[4] = { 0, 0, 1, -1 };
 
// 压缩坐标，将坐标的值变成“这是第几种值”，返回一共有几种坐标
int compress(int *x1, int *x2, int w)
{
	vector<int>xs;
 
	for (int i = 0; i < N; ++i)
	{
		int tx1 = x1[i], tx2 = x2[i];
		if (1 <= tx1 && tx1 < w) xs.push_back(tx1);
		if (1 <= tx2 && tx2 < w) xs.push_back(tx2);
	}
	xs.push_back(0);
	xs.push_back(w);
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	for (int i = 0; i < N; ++i)
	{
		x1[i] = find(xs.begin(), xs.end(), x1[i]) - xs.begin();
		x2[i] = find(xs.begin(), xs.end(), x2[i]) - xs.begin();
	}
	return xs.size() - 1;
}
 
int bfs()
{
	int ans = 0;
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			if (fld[i][j]) continue;
			++ans;
			queue<pair<int, int> >que;
			que.push(make_pair(j, i));
			while (!que.empty())
			{
				int nx = que.front().first, ny = que.front().second;
				que.pop();
 
				for (int i = 0; i < 4; ++i)
				{
					int tx = nx + dx[i], ty = ny + dy[i];
					if (tx < 0 || W < tx || ty < 0 || H< ty || fld[ty][tx] > 0) continue;
					que.push(make_pair(tx, ty));
					fld[ty][tx] = 1;
				}
			}
		}
	}
	return ans;
}
 

int main(int argc, char *argv[])
{
	while (cin >> W >> H, W | H)
	{
		cin >> N;
		for (int i = 0; i < N; ++i)
		{
			cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
		}
 
		memset(fld, 0, sizeof(fld));
 
		W = compress(X1, X2, W);
		H = compress(Y1, Y2, H);
 
		// imos-法
		for (int i = 0; i < N; i++)
		{
			fld[Y1[i]][X1[i]]++;
			fld[Y1[i]][X2[i]]--;
			fld[Y2[i]][X1[i]]--;
			fld[Y2[i]][X2[i]]++;
		}
		// 横向累积
		for (int i = 0; i < H; i++)
		{
			for (int j = 1; j < W; j++)
			{
				fld[i][j] += fld[i][j - 1];
			}
		}
		// 纵向累积
		for (int i = 1; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				fld[i][j] += fld[i - 1][j];
			}
		}// 累积完后，fld中非0部分表示有挡板
		cout << bfs() << endl;
	}
	return 0;
}
