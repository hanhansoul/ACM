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
/**
最长不降子序列 O(NlogN)
**/
#define MAXN 100010

int N;
int E[MAXN], F[MAXN], len, pos;
int main()
{
	// freopen("input.txt", "r", stdin);
	memset(F, 0, sizeof(F));
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &E[i]);
	len = 0;
	for (int i = 1; i <= N; i++)
	{
		pos = lower_bound(F + 1, F + len + 1, E[i]) - (F + 1);
		if (pos + 1 > len) F[++len] = E[i];
		else if (F[pos + 1] > E[i]) F[pos + 1] = E[i];
	}
	printf("%d\n", len);
	return 0;
}
