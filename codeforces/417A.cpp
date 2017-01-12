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

#define MAXN 10100
int N, M, C, D, K;
int F[MAXN];

int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d%d", &C, &D, &N, &M, &K);
	memset(F, -1, sizeof(F));
	int mx = N * M;
	F[0] = 0;
	for (int i = 0; i <= mx; i++)
	{
		if (F[i] == -1) continue;
		if (i + N <= mx && (F[i + N] == -1 || F[i + N] > F[i] + C))
			F[i + N] = F[i] + C;
	}
	for (int i = 0; i <= mx; i++)
	{
		if (F[i] == -1) continue;
		if (i + 1 <= mx && (F[i + 1] == -1 || F[i + 1] > F[i] + D))
			F[i + 1] = F[i] + D;
	}
	int ans = MAXN;
	for (int i = mx - K; i <= mx; i++)
        if(F[i] != -1)
            ans = min(ans, F[i]);
	cout << ans << endl;
	return 0;
}
