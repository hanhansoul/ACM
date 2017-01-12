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

#define MAXN 110
#define INF 1000000000
#define inf 1000000

int N, M;
vector<int> C;
vector< pair<int, int> > J;
int ans;
int Nx, Ny;
int S[MAXN][MAXN], lx[MAXN], ly[MAXN], slack[MAXN], link[MAXN];
bool visx[MAXN], visy[MAXN];
bool find(int x)
{
	visx[x] = true;
	for (int y = 1; y <= Ny; y++)
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
			else if (slack[y] > tt)
				slack[y] = tt;
		}
	return false;
}

int KM()
{
	memset(link, -1, sizeof(link));
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for (int i = 1; i <= Nx; i++)
	{
		lx[i] = -INF;
		for (int j = 1; j <= Ny; j++)
			if (S[i][j] > lx[i])
				lx[i] = S[i][j];
	}
	for (int i = 1; i <= Nx; i++)
	{
		for (int j = 1; j <= Ny; j++)
			slack[j] = INF;
		for (;;)
		{
			memset(visx, false, sizeof(visx));
			memset(visy, false, sizeof(visy));
			if (find(i)) break;
			int dd = INF;
			for (int y = 1; y <= Ny; y++)
				if (!visy[y] && dd > slack[y])
					dd = slack[y];
			for (int x = 1; x <= Nx; x++)
				if (visx[x])
					lx[x] -= dd;
			for (int y = 1; y <= Ny; y++)
				if (visy[y])
					ly[y] += dd;
				else
					slack[y] -= dd;
		}
	}
	int res = 0;
	for (int i = 1; i <= Ny; i++)
		if (link[i] != -1)
			res += S[link[i]][i];
	return res;
}
int main()
{
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	scanf("%d%d", &N, &M);
	char sign[5];
	for (int i = 1, k; i <= N; i++)
	{
		scanf("%s%d", sign, &k);
		if (sign[0] == 'A') J.push_back(make_pair(0, k));
		else J.push_back(make_pair(1, k));
	}
	for (int i = 1, k; i <= M; i++)
	{
		scanf("%d", &k);
		C.push_back(k);
	}
	memset(S, 0, sizeof(S));
	for (int i = 0; i < C.size(); i++)
		for (int j = 0; j < J.size(); j++)
		{
			if (J[j].first == 0 && C[i] >= J[j].second)
				S[i + 1][j + 1] = C[i] - J[j].second;
			else if (J[j].first == 1 && C[i] > J[j].second)
				S[i + 1][j + 1] = 0;
		}

	Nx = Ny = max(N, M);
	ans = KM();
	if (M > N)
	{
		memset(S, 0, sizeof(S));
		for (int i = 0; i < C.size(); i++)
			for (int j = 0; j < J.size(); j++)
			{
				if (J[j].first == 0)
				{
					if (C[i] >= J[j].second) S[i + 1][j + 1] = C[i] - J[j].second;
					else S[i + 1][j + 1] = -inf;
				}
				else if (J[j].first == 1)
				{
					if (C[i] > J[j].second) S[i + 1][j + 1] = 0;
					else S[i + 1][j + 1] = -inf;
				}
			}
		for (int i = 0; i < C.size(); i++)
			for (int j = N; j < M; j++)
				S[i + 1][j + 1] = C[i];
		int r = KM();
		ans = max(ans, r);
	}
	printf("%d\n", ans);
	return 0;
}
