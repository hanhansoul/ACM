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
#define MAXN 1010

int N, M;
int E[MAXN][MAXN], D[MAXN][MAXN];
int Fau[MAXN][MAXN], Fad[MAXN][MAXN], Fal[MAXN][MAXN], Far[MAXN][MAXN];
int Fbu[MAXN][MAXN], Fbd[MAXN][MAXN], Fbl[MAXN][MAXN], Fbr[MAXN][MAXN];

inline int cal(int a, int b, int c, int d)
{
	if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
	return a + b + c + d;
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &E[i][j]);

	memset(Fau, -1, sizeof(Fau));
	memset(Fad, -1, sizeof(Fad));
	memset(Fal, -1, sizeof(Fal));
	memset(Far, -1, sizeof(Far));

	memset(Fbu, -1, sizeof(Fbu));
	memset(Fbd, -1, sizeof(Fbd));
	memset(Fbl, -1, sizeof(Fbl));
	memset(Fbr, -1, sizeof(Fbr));

	memset(D, 0, sizeof(D));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			D[i][j] = max(D[i - 1][j], D[i][j - 1]) + E[i][j];
			if (i - 1) Fau[i][j] = D[i - 1][j];
			if (j - 1) Fal[i][j] = D[i][j - 1];
		}
	memset(D, 0, sizeof(D));
	for (int i = N; i > 0 ; i--)
		for (int j = 1; j <= M; j++)
		{
			D[i][j] = max(D[i + 1][j], D[i][j - 1]) + E[i][j];
			if (i + 1 <= N) Fbd[i][j] = D[i + 1][j];
			if (j - 1) Fbl[i][j] = D[i][j - 1];
		}
	memset(D, 0, sizeof(D));
	for (int i = N; i > 0; i--)
		for (int j = M; j > 0; j--)
		{
			D[i][j] = max(D[i + 1][j], D[i][j + 1]) + E[i][j];
			if (i + 1 <= N) Fad[i][j] = D[i + 1][j];
			if (j + 1 <= M) Far[i][j] = D[i][j + 1];
		}
	memset(D, 0, sizeof(D));
	for (int i = 1; i <= N; i++)
		for (int j = M; j > 0; j--)
		{
			D[i][j] = max(D[i - 1][j], D[i][j + 1]) + E[i][j];
			if (i - 1) Fbu[i][j] = D[i - 1][j];
			if (j + 1 <= M) Fbr[i][j] = D[i][j + 1];
		}

	int ans = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			ans = max(ans, cal(Fau[i][j], Fad[i][j], Fbl[i][j], Fbr[i][j]));
			ans = max(ans, cal(Fal[i][j], Far[i][j], Fbu[i][j], Fbd[i][j]));
		}
	printf("%d\n", ans);
	return 0;
}
