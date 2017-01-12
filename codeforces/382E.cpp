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

int N, K;
LL C[60][60];
LL F[60][60][2];

void cal(LL &w, LL x, LL y, LL z)
{
    // w = (w + x * y % MOD * z % MOD) % MOD;
	LL t = x * y;
	t = t >= MOD ? t % MOD : t;
	t = t * z;
	t = t >= MOD ? t % MOD : t;
	w = w + t;
	w = w >= MOD ? w % MOD : w;
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	if (N <= 1)
	{
		cout << 0 << endl;
		return 0;
	}

	C[0][0] = 1LL;
	for (int i = 1; i <= 55; i++)
	{
		C[i][0] = 1LL;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}

	F[1][0][0] = F[0][0][1] = 1LL;
	for (int i = 2; i <= N; i++)
		for (int j = 1; j <= i / 2; j++)
			for (int l = 0, r = i - 1; l <= r; l++, r--)
				for (int k = 0; k <= j; k++)
				{
					LL sum;
					if (l == r) sum = C[i - 2][l - 1];  // ?
					else sum = C[i - 1][l];
					if (l) sum = sum * l % MOD * r % MOD;
					else sum = sum * r % MOD;
					cal(F[i][j][0], F[l][k][1], F[r][j - k][1], sum);
					cal(F[i][j][1], F[l][k][1], F[r][j - k - 1][0], sum);
					cal(F[i][j][1], F[l][k][0], F[r][j - k - 1][1], sum);
					cal(F[i][j][1], F[l][k][0], F[r][j - k - 1][0], sum);
				}
	cout << (F[N][K][0] + F[N][K][1]) % MOD << endl;
	return 0;
}






