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
#define LL long long
#define MOD 1000000007

int T, N, K;
LL F[55][1010], R[55][1010];
LL C[1010][55], P[55];

int main()
{
	// freopen("input.txt", "r", stdin);
	F[0][0] = 1;
	for (int i = 1; i <= 1000; i++)
		for (int j = 1000; j >= i; j--)
			for (int k = 50; k >= 1; k--)
				F[k][j] = (F[k][j] + F[k - 1][j - i]) % MOD;

	C[0][0] = 1;
	for (int i = 1; i <= 1000; i++)
	{
		C[i][0] = 1;
		for (int j = 1; j <= 50; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}

	P[0] = 1;
	for (int i = 1; i <= 50; i++)
		P[i] = (P[i - 1] * i) % MOD;

	memset(R, 0, sizeof(R));
	for (int i = 1; i <= 50; i++)
		for (int j = 1; j <= 1000; j++)
        {
            for (int k = 1; k <= j; k++)
				R[i][j] = (R[i][j] + F[i][k] * C[i + j - k][i] % MOD) % MOD;
            R[i][j] = (R[i][j] * P[i]) % MOD;
        }

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &K);
		if (K > 45) printf("0\n");
		else printf("%d\n", (int)R[K][N]);
	}
	return 0;
}
