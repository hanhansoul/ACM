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

int N, K, W;
char S[MAXN];
int E[MAXN], T[MAXN], R[12][MAXN];
int solve(int l, int r)
{
	int m = l % K;
	int s = T[r] - T[l - 1];
	return (r - l + 1) / K - (R[m][r] - R[m][l - 1]) + s - (R[m][r] - R[m][l - 1]);
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &N, &K, &W);
	scanf("%s", S);
	memset(E, 0, sizeof(E));
	memset(R, 0, sizeof(R));
	for (int i = 0; i < N; i++)
	{
		E[i + 1] = S[i] - '0';
		T[i + 1] = T[i] + E[i + 1];
	}
	for (int k = 1; k <= K; k++)
	{
		int m = k == K ? 0 : k;
		int rec = k + K - 1;
		for (int i = 1; i <= N; i++)
		{
			if (i == rec) R[m][i] = R[m][i - 1] + E[i], rec += K;
			else R[m][i] = R[m][i - 1];
		}
	}
	// for (int i = 1; i <= N; i++)
	//	cout << R[1][i] << endl;

	for (int i = 1; i <= W; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", solve(l, r));
	}
	return 0;
}
