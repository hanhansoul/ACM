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

#define INF 0x3f3f3f3f

int N, M;
int E[110], F[(1 << 20)];
vector< pair<char, int> > Q;
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &E[i]);
	scanf("%d", &M);
	int y;
	char ch;
	for (int i = 0; i < M; i++)
	{
		cin >> ch >> y;
		Q.push_back(make_pair(ch, y));
	}
	sort(E, E + N, greater<int>());
	//
	int mx = (1 << M) - 1;
	for (int i = 1; i <= mx; i++)
	{
		int nn = M - __builtin_popcount(i);
		ch = Q[nn].first, y = Q[nn].second;
		if (y == 1)
		{
			F[i] = -INF;
			for (int j = 0; j < M; j++)
				if (i & (1 << j))
					F[i] = max(F[i], F[i ^ (1 << j)] + (ch == 'p' ? E[j] : 0));
		}
		else
		{
			F[i] = INF;
			for (int j = 0; j < M; j++)
				if (i & (1 << j))
					F[i] = min(F[i], F[i ^ (1 << j)] - (ch == 'p' ? E[j] : 0));
		}
	}
	cout << F[mx] << endl;
	return 0;
}
