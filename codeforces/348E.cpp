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
int N, M;
bool C[MAXN];
int edge[MAXN << 1], head[MAXN], next[MAXN << 1], len[MAXN << 1], tot;
void addedge(int a, int b, int c)
{
	edge[tot] = b, len[tot] = c, next[tot] = head[a], head[a] = tot++;
}

int D[MAXN], P[MAXN], S[MAXN], F[MAXN];
int fa[MAXN], dfn[MAXN], cnt;
bool vis[MAXN];
/*
  dfs用于计算D[], P[]和dfn[]
  首先指定一个节点s为树的根节点
  D[i]表示节点i到节点s的距离
  P[i]表示节点i属于节点s的儿子节点编号
  dfn[]表示节点遍历的顺序
*/
void dfs(int rt, int ff)
{
	dfn[++cnt] = rt;
	fa[rt] = ff;
	for (int i = head[rt]; i != -1; i = next[i])
		if (edge[i] != ff)
		{
			int u = edge[i];
			D[u] = D[rt] + len[i];
			P[u] = !ff ? u : P[rt];
			dfs(u, rt);
		}
}

int solve(int rt)
{
	cnt = D[rt] = P[rt] = 0;
	dfs(rt, 0);
	int mx = 0, ret = rt;
	for (int i = 1; i <= N; i++)
		if (D[i] > mx && C[i]) ret = i, mx = D[i];
	return ret;
}

int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	memset(C, false, sizeof(C));
	int x;
	for (int i = 1; i <= M; i++)
	{
		scanf("%d", &x);
		C[x] = true;
	}
	memset(head, -1, sizeof(head));
	tot = 0;
	for (int i = 1; i < N; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addedge(a, b, c);
		addedge(b, a, c);
	}
	// 两次dfs后可求出树的一条直径，直径的两端点为st和en。
	// 现在构造的是一棵以mid为根的树，mid为所求的直径的中点位置上的节点。
	// 之后以mid为根，求出D[]，P[]和dfn[]
	int st = solve(x);
	int en = solve(st);
	int mid = fa[en];
	while (D[mid] > D[en] / 2)
		mid = fa[mid];
	solve(mid);

	memset(vis, false, sizeof(vis));
	cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		if (!C[i] || vis[P[i]]) continue;
		if (D[en] == D[i])
			cnt++, vis[P[i]] = true;
	}

    // P[i] == P[st]表示i与st在同一子树下，最长路径为 i ==> en
    // P[i] == P[en]表示i与en在同一子树下，最长路径为 i ==> st
    // P[i] != P[st] && P[i] != P[en]表示i与st和en都不在同一子树下，最长路径为 i ==> en
    // S[i]表示以节点i为终点的monastery节点的数量
	memset(S, 0, sizeof(S));
	for (int i = 1; i <= N; i++)
		if (C[i])
		{
			S[i]++;
			if (P[i] == P[st] && cnt <= 2) S[en]++;
			else if (P[i] == P[en] && cnt <= 2) S[st]++;
			else if (P[i] != P[en] && P[i] != P[st] && cnt == 1) S[en]++;
		}

	int anst = 0, answ = 0;
	if (!C[mid]) anst = M, answ = 1;
	for (int i = N; i > 1; i--)
	{
		int u = dfn[i];
		S[fa[u]] += S[u];
		if (C[u]) continue;
		if (anst < S[u]) anst = S[u], answ = 1;
		else if (anst == S[u]) answ++;
	}
	cout << anst << " " << answ << endl;
	return 0;
}
