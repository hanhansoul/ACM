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

const double eps = 1e-8;
int N, mx;
double F[(1 << 20) + 10], L, R;
double  x[25], y[25], a[25];

int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%lf%lf", &N, &L, &R);
	for (int i = 1; i <= N; i++)
	{
		scanf("%lf%lf%lf", &x[i], &y[i], &a[i]);
		a[i] *= acos(-1.0)/180;
	}

	mx = (1 << N) - 1;
	for (int i = 0; i <= mx; i++) F[i] = -1e8;
	F[0] = L;
	for (int i = 0; i <= mx; i++)
    {
		for (int j = 1; j <= N; j++)
		{
			int v = 1 << (j - 1);
			if (i & v) continue;
			double an = atan2(-y[j], -x[j] + F[i]);
			an += a[j];
			if (an + eps > 0.0)
			{
				printf("%.10lf\n", R - L);
				return 0;
			}
			F[i | v] = max(F[i | v], x[j] - y[j] / tan(an));
		}
    }

	printf("%.10lf\n", min(R - L, F[mx] - L));
	return 0;
}
