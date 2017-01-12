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
#define MAXN 100010

int K, N, maxb, T;
int L[MAXN], D[MAXN], S[MAXN];
int solve()
{
	if (maxb <= T || N <= T)
	{
		sort(S + 1, S + N + 1);
		return unique(S + 1, S + N + 1) - (S + 1);
	}
	else
	{
		int ans = 0;
		memset(D, 0, sizeof(D));
		for (int i = 1; i <= T; i++)
			for (int j = 1; j <= N; j++)
			{
				int t = S[j];
				for (; L[D[t]] < t && D[t] <= ans; D[t]++);
				// L[k]表示长度为k的序列的列尾数字
				L[D[t]] = t;
				ans = max(ans, D[t]);
			}
		return ans;
	}
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d", &K, &N, &maxb, &T);
	while (K--)
	{
		for (int i = 1; i <= N; i++)
			scanf("%d", &S[i]);
		printf("%d\n", solve());
	}
	return 0;
}
