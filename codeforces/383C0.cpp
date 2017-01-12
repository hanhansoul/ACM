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
#define MAXN 200010
int N, M, E[MAXN];
int head[MAXN], next[MAXN], edge[MAXN], tot;
inline void addedge(int x, int y)
{
	edge[tot] = y, next[tot] = head[x], head[x] = tot++;
}

int cate[MAXN], Q[MAXN], R[MAXN], ltot;
void dfs(int rt, int ff, int level)
{
	cate[rt] = level, Q[++ltot] = rt;
	for (int i = head[rt]; i != -1; i = next[i])
		if (edge[i] != ff)
			dfs(edge[i], rt, 1 - level);
	return;
}

int G[2][MAXN], pg[2], st[MAXN][2], en[MAXN][2];
int create_index(int rt, int ff, int c)
{
	int mx = 0, r = 0, stmi = 0, str = 0;
	if (cate[rt] == c) mx = R[rt], r = rt;
	for (int i = head[rt]; i != -1; i = next[i])
		if (edge[i] != ff)
		{
			int t = create_index(edge[i], rt, c);
			if (t && R[t] > mx) mx = R[t], r = t;
			if (stmi == 0 || R[edge[i]] < stmi) stmi = R[edge[i]], str = edge[i];
		}
	if (cate[rt] == c)
	{
		st[rt][c] = R[rt];
		st[rt][1 - c] = stmi;
	}
	en[rt][c] = mx;
	return r;
}

// segment tree
struct TREE
{
	int lab;
	struct NODE
	{
		int tt, dd;
	}T[MAXN << 2];
	TREE()
	{
		memset(T, 0, sizeof(T));
	}
	void push_down(int rt)
	{
		T[rt << 1].dd += T[rt].dd;
		T[rt << 1 | 1].dd += T[rt].dd;
		T[rt].dd = 0;
	}
	void build(int rt, int L, int R)
	{
		if (L > R) return;
		if (L == R)
		{
			T[rt].tt = E[G[lab][L]];
			T[rt].dd = 0;
			return;
		}
		int mid = (L + R) >> 1;
		build(rt << 1, L, mid);
		build(rt << 1 | 1, mid + 1, R);
		return;
	}
	void Insert(int rt, int L, int R, int l, int r, int vv)
	{
		if (r < L || l > R) return;
		if (l <= L && R <= r)
		{
			T[rt].dd += vv;
			return;
		}
		int mid = (L + R) >> 1;
		push_down(rt);
		Insert(rt << 1, L, mid, l, r, vv);
		Insert(rt << 1 | 1, mid + 1, R, l, r, vv);
		return;
	}
	void Query(int rt, int L, int R, int nn, int &a)
	{
		if (nn < L || nn > R) return;
		if (L == R)
		{
			a = T[rt].tt + T[rt].dd;
			return;
		}
		int mid = (L + R) >> 1, t1, t2;
		push_down(rt);
		Query(rt << 1, L, mid, nn, a);
		Query(rt << 1 | 1, mid + 1, R, nn, a);
		return;
	}
}T[2];

int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &E[i]);
	memset(head, -1, sizeof(head));
	tot = 0;
	for (int i = 1; i < N; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y);
		addedge(y, x);
	}
	ltot = 0;
	dfs(1, 0, 0);
	for (int i = 1; i <= ltot; i++)
	{
		int lab = cate[Q[i]];
		G[lab][++pg[lab]] = Q[i];
		R[Q[i]] = pg[lab];
	}
	create_index(1, 0, 0);
	create_index(1, 0, 1);
	// solve
	T[0].lab = 0;
	T[1].lab = 1;
	T[0].build(1, 1, pg[0]);
	T[1].build(1, 1, pg[1]);
	int s, n, val, a, c;
	while (M--)
	{
		scanf("%d", &s);
		if (s == 1)
		{
			scanf("%d%d", &n, &val);
			c = cate[n];
			if (st[n][c] && en[n][c])
				T[c].Insert(1, 1, pg[c], st[n][c], en[n][c], val);
			c = 1 - c;
			if (st[n][c] && en[n][c])
				T[c].Insert(1, 1, pg[c], st[n][c], en[n][c], -val);
		}
		else if (s == 2)
		{
			scanf("%d", &n);
			c = cate[n];
			T[c].Query(1, 1, pg[c], R[n], a);
			printf("%d\n", a);
		}
	}

	return 0;
}
