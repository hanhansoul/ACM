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
#define MAXN 3010

int N, K;
int P[MAXN], F[MAXN][MAXN];
bool S1[MAXN], S0[MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++)
		scanf("%d", &P[i]);
	S0[N + 1] = true;
	S1[N + 1] = false;
	for (int i = N; i >= 1; i--)
	{
		S0[i] = S0[i + 1] && (P[i] == 0);
		S1[i] = S1[i + 1] || (P[i] == 100);
	}
	// solve
	if (N == 1)
	{
		printf("1\n");
		return 0;
	}
	memset(F, 0x3f, sizeof(F));
	F[1][2] = 0;
	for (int i = 2; i <= N; i++)
	{
		for (int j = 1; j < i; j++)
		{
			// F[j][i]
			if (F[j][i] >= K) continue;
			if (!S0[i] && P[j] != 100)
				F[i][i + 1] = min(F[i][i + 1], F[j][i] + 1);
			if (!S1[i] && P[j] != 0)
				F[j][i + 1] = min(F[j][i + 1], F[j][i] + 1);
			if (!S0[i] && P[j] != 0)
				F[i + 1][i + 2] = min(F[i + 1][i + 2], F[j][i] + 1);
		}
	}
	int ans = 0;
	for (int i = 1; i <= N + 2; i++)
		for (int j = i; j <= N + 2; j++)
			if (F[i][j] <= K) ans++;
	printf("%d\n", ans);
	return 0;
}
