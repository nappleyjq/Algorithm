/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0118

Property Distribution

タナカ氏が HW アールの果樹園を残して亡くなりました。果樹園は東西南北方向に H × W の区画に分けられ、区画ごとにリンゴ、カキ、ミカンが植えられています。タナカ氏はこんな遺言を残していました。

果樹園は区画単位でできるだけ多くの血縁者に分けること。ただし、ある区画の東西南北どれかの方向にとなりあう区画に同じ種類の果物が植えられていた場合は、区画の境界が分からないのでそれらは 1 つの大きな区画として扱うこと。

例えば次のような 3 × 10 の区画であれば ('リ'はリンゴ、'カ'はカキ、'ミ'はミカンを表す)

同じ樹がある区画の間の境界を消すと次のようになり、

結局 10 個の区画、つまり 10 人で分けられることになります。

雪が降って区画の境界が見えなくなる前に分配を終えなくてはなりません。あなたの仕事は果樹園の地図をもとに分配する区画の数を決めることです。

果樹園の地図を読み込み、分配を受けられる血縁者の人数を出力するプログラムを作成してください。
Input

複数のデータセットが与えられます。各データセットは空白で区切られた H, W (H, W ≤ 100) を含む行から始まり、続いて H × W の文字からなる H 行の文字列が与えられます。この文字列には、リンゴを表す '@'、カキを表す '#'、ミカンを表す '*'、の 3 文字しか現れません。

入力はゼロが２つの行で終わります。データセットの数は 20 を超えません。
Output

各データセットごとに、分配を受ける人数を１行に出力してください。
Sample Input

10 10
####*****@
@#@@@@#*#*
@##***@@@*
#****#*@**
##@*#@@*##
*@@@@*@@@#
***#@*@##*
*@@@*@@##@
*@*#*@##**
@****#@@#@
0 0

Output for the Sample Input

33

*/

/*
Solution:depth first search
*/

#include <iostream>
using namespace std;
 
#define MAX_W 100
#define MAX_H 100
char farm[MAX_W][MAX_H];
int W, H;
const int direction[4][2] = {
	{ -1, 0 },
	{ 1, 0 },
	{ 0, -1 },
	{ 0, 1 },
};
 
void dfs(const int& x, const int& y, const char tree)
{
	farm[x][y] = 'x';
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + direction[i][0];
		int ny = y + direction[i][1];
		if (nx >= 0 && nx < W && ny >= 0 && ny < H && farm[nx][ny] == tree)
		{
			dfs(nx, ny, tree);
		}
	}
}
 
int main(int argc, char *argv[])
{
 
	while (cin >> H >> W, W > 0)
	{
		int res = 0;
		int x, y;
		for (y = 0; y < H; ++y)
		{
			for (x = 0; x < W; ++x)
			{
				cin >> farm[x][y];
			}
		}
 
		for (y = 0; y < H; ++y)
		{
			for (x = 0; x < W; ++x)
			{
				if (farm[x][y] != 'x')
				{
					dfs(x, y, farm[x][y]);
					++res;
				}
			}
		}
		cout << res << endl;
	}
 
	return 0;
}
