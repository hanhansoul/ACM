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
#define MAXN 4010

int N, K;
int S[MAXN][MAXN], F[MAXN][MAXN], C[MAXN][MAXN], E[MAXN][MAXN];
void GET(int &t)
{
	char c;
	t = 0;
	do
	{
		c = getchar();
	}
	while (!isdigit(c));
	while (isdigit(c))
	{
		t = t * 10 + c - '0';
		c = getchar();
	}
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
        {
            // scanf("%d", &S[i][j]);
            GET(S[i][j]);
            F[i][j] = 0x6f7f7f7f;
        }

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			S[i][j] = S[i][j] + S[i - 1][j] +
			          S[i][j - 1] - S[i - 1][j - 1];

	for (int i = 1; i <= N; i++)
		for (int j = i; j <= N; j++)
			C[i][j] = (S[j][j] - S[i - 1][j] -
			           S[j][i - 1] + S[i - 1][i - 1]) / 2;

	for (int i = 1; i <= N; i++)
		F[1][i] = C[1][i], E[1][i] = 0;

	for (int i = 2; i <= K; i++)
	{
		E[i][N + 1] = N;
		for (int j = N; j >= i; j--)
			for (int k = E[i - 1][j]; k <= E[i][j + 1]; k++)
				if (F[i - 1][k] + C[k + 1][j] < F[i][j])
				{
					F[i][j] = F[i - 1][k] + C[k + 1][j];
					E[i][j] = k;
				}
	}
	printf("%d\n", F[K][N]);
	return 0;
}
