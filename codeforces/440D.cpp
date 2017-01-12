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
#define MAXN 410

int N, K;
int F[MAXN][MAXN], C[MAXN];
int head[MAXN], edge[MAXN * MAXN], next[MAXN * MAXN], tot;
void addedge(int x, int y)
{
	edge[tot] = y, next[tot] = head[x], head[x] = tot++;
}
int dfs(int rt, int ff)
{
    C[rt] = 1;
    int cnt = 0;
	for (int i = head[rt]; i != -1; i = next[i])
        if(edge[i] != ff)
        {
            C[rt] += dfs(edge[i]);
            cnt++;
        }
    F[rt][1] = cnt;
    int u;
    for (int i = head[rt]; i != -1; i = next[i])
    {
        u = edge[i];
        for(int k = min(C[rt], K); k >= 1; k--)
        {
            F[rt][k] = min(F[rt][k], F[rt][k - j] + F[u][j] - 1);
        }
    }
    C[rt]++;
    return C[rt];
}
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	memset(head, -1, sizeof(head));
	tot = 0;
	for (int i = 1; i <= N; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y);
		addedge(y, x);
	}
	dfs(1, 0);
	return 0;
}
