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
#define MAXN 1010

int w, b;
double F[2][MAXN][MAXN];
bool V[2][MAXN][MAXN];
double dfs(int n, int w, int b)
{
	if (w < 0 || b < 0) return 0;
	if (V[n][w][b]) return F[n][w][b];
	if (n == 0)
	{
		F[n][w][b] += 1.0 * w / (w + b) + 1.0 * dfs(1, w, b - 1) * b / (w + b);
	}
	else
	{
		if (w + b > 1)
			F[n][w][b] += (1.0 * dfs(0, w, b - 2) * b * (b - 1) +
			               1.0 * dfs(0, w - 1, b - 1) * b * w) / (w + b) / (w + b - 1);
		else
			F[n][w][b] += 1.0 * dfs(0, w, b - 1) * b / (w + b);
	}
	V[n][w][b] = true;
	return F[n][w][b];
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &w, &b);
	memset(F, 0, sizeof(F));
	for (int i = 1; i <= w; i++)
		F[0][i][0] = 1, V[0][i][0] = true;
	for (int i = 0; i <= b; i++)
		F[0][0][i] = 0, V[0][0][i] = true;
	dfs(0, w, b);
	printf("%.15lf\n", F[0][w][b]);
	return 0;
}





