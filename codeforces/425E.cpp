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
#define LL long long
#define MOD 1000000007

int N, K;
LL F[MAXN][MAXN], P[MAXN * MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	P[0] = 1;
	for (int i = 1; i <= N * N; i++)
		P[i] = (P[i - 1] << 1) % MOD;
	memset(F, 0, sizeof(F));
	F[0][0] = 1;
	for (int i = 1; i <= N; i++)
	{
		F[i][0] = 1;
		for (int j = 1; j <= min(i, K); j++)
			for (int k = 0; k < i; k++)
			{
				// F[i][j] = F[k][j - 1] * (2 ^ (i - k) - 1) * 2 ^ ((i - k) * k);
				F[i][j] = (F[i][j] + (F[k][j - 1] * (P[i - k] - 1) % MOD) * P[(i - k) * k] % MOD) % MOD;
			}
	}
	cout << F[N][K] << endl;
	return 0;
}
