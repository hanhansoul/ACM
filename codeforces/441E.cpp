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

int N, K, P;
double F[210][210];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &N, &K, &P);
	double pp = 1.0 * P / 100;
	memset(F, 0, sizeof(F));
	for (int i = 0; i <= K; i++)
        F[0][i] = __builtin_ctz(N + i);

	for (int i = 1; i <= K; i++)
		for (int j = 0; j <= K; j++)
		{
			F[i][j] += F[i - 1][j + 1] * (1 - pp);
			if (!(j & 1)) F[i][j] += (F[i - 1][j >> 1] + 1) * pp;
		}
	printf("%.10lf\n", F[K][0]);
	return 0;
}
