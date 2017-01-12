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
#define MAXN 160
#define LL long long
#define MOD 1000000007

int N, M;
LL F[MAXN][MAXN][2][MAXN][2];
LL D[MAXN][MAXN][2][MAXN][2];
LL ans;
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	int l, r;
	ans = 0LL;
	for (int i = 1; i <= N; i++)
	{
		for (l = 1; l <= M; l++)
			for (r = l; r <= M; r++)
			{
				F[i][l][0][r][0] = (D[i - 1][l][0][r][0] + 1) % MOD;

				F[i][l][1][r][0] = ((D[i - 1][1][0][r][0] - D[i - 1][l][0][r][0] - D[i - 1][1][0][l - 1][0] + 2 * MOD) % MOD +
				                    (D[i - 1][1][1][r][0] - D[i - 1][l + 1][1][r][0] - D[i - 1][1][1][l - 1][0] + 2 * MOD) % MOD) % MOD;

				F[i][l][0][r][1] = ((D[i - 1][l][0][M][0] - D[i - 1][l][0][r][0] - D[i - 1][r + 1][0][M][0] + 2* MOD) % MOD +
				                    (D[i - 1][l][0][M][1] - D[i - 1][l][0][r - 1][1] - D[i - 1][r + 1][0][M][1] + 2 * MOD) % MOD) % MOD;

				F[i][l][1][r][1] = ((D[i - 1][1][0][M][0] + D[i - 1][l][0][r][0] - D[i - 1][1][0][r][0] - D[i - 1][l][0][M][0] + 2 * MOD) % MOD +
				                    (D[i - 1][1][1][M][0] + D[i - 1][l + 1][1][r][0] - D[i - 1][1][1][r][0] - D[i - 1][l + 1][1][M][0] + 2 * MOD) % MOD +
				                    (D[i - 1][1][0][M][1] + D[i - 1][l][0][r - 1][1] - D[i - 1][1][0][r - 1][1] - D[i - 1][l][0][M][1] + 2 * MOD) % MOD +
				                    (D[i - 1][1][1][M][1] + D[i - 1][l + 1][1][r - 1][1] - D[i - 1][1][1][r - 1][1] - D[i - 1][l + 1][1][M][1] + 2 * MOD) % MOD) % MOD;

				for (int x = 0; x < 2; x++)
					for (int y = 0; y < 2; y++)
						ans = (ans + F[i][l][x][r][y]) % MOD;

			}

		for (int ll = 1; ll <= M; ll++)
			for (int p = 1; p <= M - ll + 1; p++)
			{
				l = p, r = p + ll - 1;
				for (int x = 0; x < 2; x++)
					for (int y = 0; y < 2; y++)
						D[i][l][x][r][y] = ((D[i][l + 1][x][r][y] + D[i][l][x][r - 1][y] +
						                     F[i][l][x][r][y]) % MOD - D[i][l + 1][x][r - 1][y] + MOD) % MOD;
				/*
				D[i][l][0][r][0] = F[i][l][0][r][0] + D[i][l][0][r - 1][0] +
				                   D[i][l + 1][0][r][0] - D[i][l + 1][0][r - 1][0];

				D[i][l][1][r][0] = D[i][l][1][r - 1][0] + D[i][l + 1][1][r][0] -
				                   D[i][l + 1][1][r - 1][0] - F[i][l + 1][1][r][0];

				D[i][l][0][r][1] = D[i][l][0][r - 1][1] + D[i][l + 1][0][r][1] -
				                   D[i][l + 1][0][r - 1][1] - F[i][l][0][r - 1][1];

				D[i][l][1][r][1] = D[i][l + 1][1][r][1] + D[i][l][1][r - 1][1] -
				                   D[i][l + 1][1][r - 1][1] + F[i][l + 1][1][r - 1][1];
				*/
			}
	}
	cout << ans << endl;
	/*
	ans = 0;
	for (int x = 0; x < 2; x++)
	    for (int y = 0; y < 2; y++)
	        ans = (ans + D[N][1][x][M][y]) % MOD;
	cout << ans << endl;
	int a, b, c, d, e;
	while (true)
	{
		cin >> a >> b >> c >> d >> e;
		cout << "F: " << F[a][b][c][d][e] << endl;
		cout << "D: " << D[a][b][c][d][e] << endl;
	}
	*/
	return 0;
}
