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
#define LL long long
#define MOD 1000000007

int N;
vector<int> Q[MAXN];
LL F[MAXN][2];
bool vis[MAXN];

void dfs(int u)
{
	if (vis[u]) return;
	vis[u] = true, F[u][1] = 1LL, F[u][0] = 0LL;
	if(!Q[u].size()) return;
	LL d0, d1;
	for (int i = 0; i < Q[u].size(); i++)
	{
		int v = Q[u][i];
		dfs(v);
		d0 = (F[u][1] * F[v][1] + F[u][0] * F[v][0]) % MOD;
		d1 = (F[u][1] * F[v][0] + F[u][0] * F[v][1]) % MOD;
		F[u][0] = (F[u][0] + d0) % MOD;
		F[u][1] = (F[u][1] + d1) % MOD;
	}

	LL p0 = 1LL, p1 = 1LL, p2 = 0LL;
	for (int i = 0; i < Q[u].size(); i++)
	{
		int v = Q[u][i];
		p0 = (p0 + p0 * F[v][0]) % MOD;
		LL tmp = p1;
		p1 = (p1 + p2 * F[v][1]) % MOD;
		p2 = (p2 + tmp * F[v][1]) % MOD;
	}
    F[u][0] = (F[u][0] * 2 - p2 + MOD) % MOD;
	F[u][1] = (F[u][1] * 2 - p0 + MOD) % MOD;

	return;
}

int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 2; i <= N; i++)
	{
		int x;
		scanf("%d", &x);
		Q[x].push_back(i);
	}
	memset(vis, false, sizeof(vis));
	memset(F, 0, sizeof(F));
    dfs(1);
    cout << (F[1][0] + F[1][1]) % MOD << endl;
	return 0;
}
