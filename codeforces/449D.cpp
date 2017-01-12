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
#define MAXN 1000010
#define MOD 1000000007

int N, S[MAXN], D[MAXN], C[MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &S[i]);
		D[S[i]]++;
	}

	for (int i = 0; i < 20; i++)
		for (int j = 1000000; j >= 0; j--)
			if (j & (1 << i))
				D[(1 << i)^j] = (D[(1 << i)^j] + D[j]) % MOD;

	C[0] = 1;
	for (int i = 1; i <= N; i++)
		C[i] = (C[i - 1] << 1) % MOD;

	long long ans = 0;
	for (int i = 1000000; i >= 0; i--)
	{
		int cnt = __builtin_popcount(i);
		int e = (cnt & 1) ? (-1) : 1;
        ans = (ans + 1LL * (C[D[i]] - 1) % MOD * e + MOD) % MOD;
	}
	printf("%d\n", ans);
	return 0;
}
