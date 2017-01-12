#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>

using namespace std;

#define MAXN 300010
#define LL long long

char S[MAXN];
bool vis[30];
typedef pair<int, int> PI;
set<PI, greater<PI> > R;
set<PI, greater<PI> >::iterator it;
LL D[MAXN];
int main()
{
	//freopen("input.txt", "r", stdin);
	scanf("%s", S + 1);
	int len = strlen(S + 1), cnt = 0;
	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= len; i++)
		if (!vis[S[i] - 'a'])
		{
			cnt++;
			vis[S[i] - 'a'] = true;
			if (cnt == 26) break;
		}

	R.clear();
	for (int i = 1; i <= len; i++)
	{
		int ch = S[i] - 'a';

		for (it = R.begin(); it != R.end(); it++)
			if (it->second == ch)
			{
				R.erase(it);
				break;
			}

		int pre, pos = i, dd = 1;
		for (it = R.begin(); it != R.end(); it++)
		{
			pre = it->first;
			D[dd] += 1LL * (pos - pre);
			pos = pre;
			dd++;
		}
		D[dd] += 1LL * pos;
		R.insert(make_pair(i, ch));
	}
	cout << cnt << endl;
	for (int i = 1; i <= cnt; i++)
		cout << D[i] << endl;
	return 0;
}
