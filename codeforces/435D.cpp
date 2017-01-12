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
/*
  * * *
  * * _

  ===>

  1 2 3
  0 x _
*/
#define MAXN 410

int N, M;
char S[MAXN][MAXN];
int F[MAXN][MAXN][4];
int D[4][2] = {{0, -1}, { -1, -1}, { -1, 0}, { -1, 1}};
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%s", S[i] + 1);
	int ans = 0;
	memset(F, 0, sizeof(F));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			if (S[i][j] == '1') continue;
			for (int k = 0; k < 4; k++)
			{
				int x = i + D[k][0], y = j + D[k][1];
				if (1 <= x && x <= N && 0 <= y && y <= M && S[x][y] == '0')
					F[i][j][k] = F[x][y][k] + 1;
			}
		}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			int* p = F[i][j];
			for (int k = 1; k <= p[0] && k <= p[1]; k++)
				if (F[i][j - k][2] >= k) ans++;

			for (int k = 1; k <= p[0] && k <= p[2]; k++)
				if (F[i][j - k][3] >= k) ans++;

			for (int k = 1; k <= p[1] && k <= p[2]; k++)
				if (F[i - k][j][0] >= k) ans++;

			for (int k = 1; k <= p[2] && k <= p[3]; k++)
				if (F[i - k][j + k][0] >= k) ans++;

			for (int k = 1; k + k <= p[0] && k <= p[1]; k++)
				if (F[i][j - k - k][3] >= k) ans++;

			for (int k = 1; k + k <= p[2] && k <= p[1]; k++)
				if (F[i - k][j - k][3] >= k) ans++;

			for (int k = 1; k + k <= p[2] && k <= p[3]; k++)
				if (F[i - k][j + k][1] >= k) ans++;

			for (int k = 1; k <= p[1] && k <= p[3]; k++)
				if (F[i - k][j + k][0] >= k + k) ans++;
		}
	cout << ans << endl;
	return 0;
}
