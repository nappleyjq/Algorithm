#ifndef ONLINE_JUDGE
#pragma warning(disable : 4996)
#endif
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <stdio.h>
using namespace std;
 
///////////////////////////SubMain//////////////////////////////////
int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int n;
	cin >> n;
	vector<int> coll;
	copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(coll));
	sort(coll.begin(), coll.end(), greater<int>());
	//copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	bool found = false;
	for (int i = 0; i < n - 2; ++i)
	{
		if (coll[i] < coll[i + 1] + coll[i + 2])
		{
			cout << coll[i] + coll[i + 1] + coll[i + 2] << endl;
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << 0 << endl;
	}
#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	system("out.txt");
#endif
	return 0;
}
