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
#define MAXN 110
#define LL long long

int N, M, K, mx;
struct NODE
{
	int c, m, p;
};
NODE E[MAXN];
LL S[(1 << 20)];
bool cmp(const NODE &t1, const NODE &t2)
{
	return t1.m > t2.m;
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &N, &M, &K);
	mx = 1 << M;
	for (int i = 1, c; i <= N; i++)
	{
		scanf("%d%d%d", &E[i].c, &E[i].m, &c);
		E[i].p = 0;
		for (int j = 1, x; j <= c; j++)
		{
			scanf("%d", &x);
			E[i].p |= (1 << (x - 1));
		}
	}
	sort(E + 1, E + N + 1, cmp);
	memset(S, -1, sizeof(S));
	S[0] = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = mx - 1; j > 0; j--)
			if (S[j] != -1)
			{
				if (S[j | E[i].p] == -1 || S[j | E[i].p] > S[j] + E[i].c)
					S[j | E[i].p] = S[j] + E[i].c;
			}
        if(S[E[i].p] == -1 || S[E[i].p] > E[i].c + K * E[i].m)
            S[E[i].p] = E[i].c + 1LL * K * E[i].m;
	}
	cout << S[mx - 1] << endl;
	return 0;
}
