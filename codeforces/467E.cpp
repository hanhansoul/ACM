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
#define MAXN 500010
int N;
vector<int> E, C;
map<int, int> R;
int L[MAXN], tot, S[MAXN], top;
int instack[MAXN], mark[MAXN], P[MAXN];
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	tot = 0;
	for (int i = 1; i <= N; i++)
	{
		int x, t;
		scanf("%d", &x);
		if (R.count(x)) t = R[x];
		else R[x] = ++tot, L[tot] = x, t = tot;
		E.push_back(t);
	}

	int pos = 0;
	memset(instack, 0, sizeof(instack));
	memset(mark, 0, sizeof(mark));
	while (pos < E.size())
	{
		top = 0;
		while (pos < E.size())
		{
			int u = E[pos++], pp;
			if (instack[u])
			{
				if (mark[u])
				{
					for (int k = 0; k < 2; k++)
					{
						C.push_back(mark[u]);
						C.push_back(u);
					}
					while (top)
						mark[S[top]] = 0, instack[S[top]] = 0, P[S[top--]] = 0;
					break;
				}
				else
				{
					pp = top;
					while (pp > P[u])
						mark[S[pp--]] = u;
				}
			}
			S[++top] = u;
			instack[u]++;
			if (!P[u]) P[u] = top;
		}
	}
	printf("%d\n", C.size());
	for (int i = 0; i < C.size(); i++)
		printf("%d ", L[C[i]]);
	printf("\n");
	return 0;
}
