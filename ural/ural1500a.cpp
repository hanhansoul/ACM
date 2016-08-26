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

int N, M, K;
int E[35][35];
bool V[35];
int mi, msk;
bool dfs(int nn, int mm)
{
	if (nn == 1) return true;
	V[nn] = true;
	for (int i = 0; i < N; i++)
	{
		if (!V[i] && (E[nn][i] & mm))
		{
			if (dfs(i, mm)) return true;
		}
	}
	return false;
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &K, &N, &M);
	memset(E, 0, sizeof(E));
	for (int i = 1, a, b, c; i <= M; i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		E[a][b] |= (1 << c);
		E[b][a] = E[a][b];
	}
	mi = 0x3f3f3f3f, msk = (1 << K) - 1;
	for (int i = 1; i < (1 << K); i++)
	{
		int cnt = __builtin_popcount(i);
		if (cnt >= mi) continue;
		memset(V, false, sizeof(V));
		if (dfs(0, i)) mi = cnt, msk = i;
	}
	printf("%d\n", mi);
	for (int i = 0; i < K; i++)
		if (msk & (1 << i))
			printf("%d ", i);
	return 0;
}
