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
  dfs���ڼ���D[], P[]��dfn[]
  ����ָ��һ���ڵ�sΪ���ĸ��ڵ�
  D[i]��ʾ�ڵ�i���ڵ�s�ľ���
  P[i]��ʾ�ڵ�i���ڽڵ�s�Ķ��ӽڵ���
  dfn[]��ʾ�ڵ������˳��
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
	// ����dfs����������һ��ֱ����ֱ�������˵�Ϊst��en��
	// ���ڹ������һ����midΪ��������midΪ�����ֱ�����е�λ���ϵĽڵ㡣
	// ֮����midΪ�������D[]��P[]��dfn[]
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

    // P[i] == P[st]��ʾi��st��ͬһ�����£��·��Ϊ i ==> en
    // P[i] == P[en]��ʾi��en��ͬһ�����£��·��Ϊ i ==> st
    // P[i] != P[st] && P[i] != P[en]��ʾi��st��en������ͬһ�����£��·��Ϊ i ==> en
    // S[i]��ʾ�Խڵ�iΪ�յ��monastery�ڵ������
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
