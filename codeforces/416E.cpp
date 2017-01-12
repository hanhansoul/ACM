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

#define MAXN 510
#define INF 0x3f3f3f3f

int N, M;
int E[MAXN][MAXN], D[MAXN][MAXN], C[MAXN][MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	memset(E, 0x3f, sizeof(E));
	for (int i = 0; i < M; i++)
	{
		int x, y, d;
		scanf("%d%d%d", &x, &y, &d);
		E[x][y] = E[y][x] = d;
	}

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			D[i][j] = E[i][j];
	for (int i = 1; i <= N; i++) D[i][i] = 0;

	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

	memset(C, 0, sizeof(C));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++)
				if (E[k][j] != INF && D[i][j] == D[i][k] + E[k][j])
					C[i][j]++;

	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
		{
			int sum = 0;
			for (int k = 1; k <= N; k++)
				if (D[i][j] == D[i][k] + D[k][j])
					sum += C[i][k];
			printf("%d ", sum);
		}

	return 0;
}
