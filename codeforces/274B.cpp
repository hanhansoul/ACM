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

int N;
int edge[MAXN << 1], next[MAXN << 1], head[MAXN], tot;
int S[MAXN];
LL P[MAXN], Q[MAXN];

void addedge(int x, int y)
{
	edge[tot] = y, next[tot] = head[x], head[x] = tot++;
}

void dfs(int rt, int ff)
{
	LL mi, mx;
	mi = mx = 0LL;
	for (int i = head[rt]; i != -1; i = next[i])
	{
		int v = edge[i];
		if (v == ff) continue;
		dfs(v, rt);
		mi = min(mi, P[v]);
		mx = max(mx, Q[v]);
	}
	LL s = 1LL * S[rt] - (mi + mx);
    if(s < 0) mi += s;
    else if(s > 0) mx += s;
    P[rt] = mi, Q[rt] = mx;
    // cout << rt << " " << P[rt] << " " << Q[rt] << endl;
    return;
}
int main()
{
    freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	int x, y;
	memset(head, -1, sizeof(head));
	for (int i = 1; i < N; i++)
	{
		scanf("%d%d", &x, &y);
		addedge(x, y);
		addedge(y, x);
	}
	for (int i = 1; i <= N; i++)
		scanf("%d", &S[i]);
    dfs(1, 0);
	LL ans = Q[1] - P[1];
	cout << ans << endl;
	return 0;
}
