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
#define DEBUG 0

using namespace std;

/*
 * */
#define MAXN 100010

int N, M;
int S[MAXN], O[MAXN], mx;
int tot, C[MAXN], ll[MAXN], rr[MAXN];
int F[MAXN], D[MAXN], R[MAXN << 1];
int main()
{
#if DEBUG
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &N, &M);
	mx = 0;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &O[i]);
		mx = max(mx, O[i]);
	}
	memset(R, 0, sizeof(R));
	for (int i = 1; i <= M; i++)
	{
		scanf("%d", &S[i]);
		R[S[i]] = 1;
		mx = max(mx, S[i]);
	}
	sort(O + 1, O + N + 1);
	sort(S + 1, S + M + 1);

	for (int i = 1; i <= mx; i++)
		R[i] += R[i - 1];
	tot = 0;
	for (int i = 1; i <= N; i++)
	{
		if (i == 1 || O[i] != O[i - 1] + 1)
			tot++, C[i] = tot, ll[tot] = rr[tot] = i;
		else if (O[i] == O[i - 1] + 1)
			C[i] = tot, rr[tot] = i;
	}
	memset(F, 0, sizeof(F));
	memset(D, 0, sizeof(D));
	for (int i = 1; i <= N; i++)
	{
		int j, k;
		F[i] = max(F[i], D[ll[C[i]] - 1]);
		for (j = 1; j <= M && S[j] <= O[i]; j++)
			if ((k = i - (O[i] - S[j])) > 0)
            {
                F[i] = max(F[i], D[ll[C[k]] - 1] + R[O[i]] - R[S[j] - 1]);
                // F[i] = max(F[i], D[k - 1] + R[O[i]] - R[S[j] - 1]);
            }
		D[i] = max(D[i], D[i - 1]);
		D[i] = max(D[i], F[i]);
		if (j - 1 && S[j - 1] == O[i]) j--;
		for (; j <= M && S[j] >= O[i]; j++)
			if ((k = i + (S[j] - O[i])) <= N)
            {
                D[rr[C[k]]] = max(D[rr[C[k]]], F[i] + R[S[j]] - R[O[i]]);
                // D[k] = max(D[k], F[i] + R[S[j]] - R[O[i]]);
            }

	}
	printf("%d\n", D[N]);
	return 0;
}
