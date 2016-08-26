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
#define MAXM (1 << 20)

int N, M, K;
vector< pair<int, int> > E[35];
bool V[35][MAXM];
int mi, msk;
// bfs MLE
/*
queue< pair<int, int> > Q;
void bfs()
{
	Q.push(make_pair(0, 0));
	V[0][0] = true;
	mi = 0x3f3f3f3f;
	int nn, mm, dn, cc;
	while (!Q.empty())
	{
		nn = Q.front().first;
		mm = Q.front().second;
		Q.pop();
		if (nn == 1)
		{
			int tt = __builtin_popcount(mm);
			if (tt < mi) mi = tt, msk = mm;
			continue;
		}
		for (int i = 0; i < E[nn].size(); i++)
		{
			dn = E[nn][i].first;
			cc = (1 << E[nn][i].second);
			if (!V[dn][mm | cc])
			{
				V[dn][mm | cc] = true;
				Q.push(make_pair(dn, (mm | cc)));
			}
		}
	}
}
*/
//dfs TLE
void dfs(int nn, int mm)
{
	if (__builtin_popcount(mm) >= mi) return;
	if (nn == 1)
	{
		int tt = __builtin_popcount(mm);
		if (tt < mi) mi = tt, msk = mm;
		return;
	}
	int dn, cc, cnt;
	for (int i = 0; i < E[nn].size(); i++)
	{
		dn = E[nn][i].first;
		cc = (1 << E[nn][i].second);
		if (!V[dn][mm | cc])
		{
			V[dn][mm | cc] = true;
			dfs(dn, mm | cc);
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &K, &N, &M);
	for (int i = 1, a, b, c; i <= M; i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		E[a].push_back(make_pair(b, c));
		E[b].push_back(make_pair(a, c));
	}
	memset(V, false, sizeof(V));
	V[0][0] = true, mi = 0x3f3f3f3f, msk = 0;
	// bfs();
	dfs(0, 0);
	printf("%d\n", mi);
	for (int i = 0, k; i < K; i++)
		if (msk & (1 << i))
			printf("%d ", i);
	return 0;
}
