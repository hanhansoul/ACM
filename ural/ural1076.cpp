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
#define MAXN 155
#define INF 0x3f3f3f3f

int N;
int T[MAXN][MAXN], E[MAXN][MAXN], ans;
int S[MAXN][MAXN], lx[MAXN], ly[MAXN], slack[MAXN];
int link[MAXN];
bool visx[MAXN], visy[MAXN];
bool find(int x)
{
	visx[x] = true;
	for (int y = 1; y <= N; y++)
		if (!visy[y])
		{
			int tt = lx[x] + ly[y] - S[x][y];
			if (tt == 0)
			{
				visy[y] = true;
				if (link[y] == -1 || find(link[y]))
				{
					link[y] = x;
					return true;
				}
			}
			else
				slack[y] = min(slack[y], tt);
		}
	return false;
}
int KM()
{
	memset(link, -1, sizeof(link));
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for (int i = 1; i <= N; i++)
    {
        lx[i] = -INF;
        for (int j = 1; j <= N; j++)
			if (S[i][j] > lx[i])
				lx[i] = S[i][j];
    }

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			slack[j] = INF;
		for (;;)
		{
			memset(visx, false, sizeof(visx));
			memset(visy, false, sizeof(visy));
			if (find(i)) break;
			int dd = INF;
			for (int y = 1; y <= N; y++)
				if (!visy[y])
					dd = min(dd, slack[y]);
			for (int x = 1; x <= N; x++)
				if (visx[x])
					lx[x] -= dd;
			for (int y = 1; y <= N; y++)
				if (visy[y])
					ly[y] += dd;
				else
					slack[y] -= dd;
		}
	}
	int ans = 0;
	for (int i = 1; i <= N; i++)
		if (link[i] != -1)
			ans += S[link[i]][i];
	return (-1) * ans;
}

int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	int cnt = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			scanf("%d", &T[i][j]);
	for (int i = 1; i <= N; i++)
	{
		int t = 0;
		for (int j = 1; j <= N; j++)
			t += T[j][i];
		for (int j = 1; j <= N; j++)
			S[j][i] = -1 * (t - T[j][i]);
	}
	ans = KM();
	printf("%d\n", ans);
	return 0;
}
