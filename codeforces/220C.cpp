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

int N, Sa[MAXN], Sb[MAXN], P[MAXN];
set< pair<int, int> > L, R;
int E[MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &Sa[i]);
		P[Sa[i]] = i;
	}
	int mi = MAXN << 2;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &Sb[i]);
		if (P[Sb[i]] <= i)
		{
			R.insert(make_pair(i - P[Sb[i]], Sb[i]));
			E[Sb[i]] = i - P[Sb[i]];
		}
		else
		{
			L.insert(make_pair(P[Sb[i]] - i, Sb[i]));
			E[Sb[i]] = P[Sb[i]] - i;
		}
		mi = min(mi, abs(P[Sb[i]] - i));
	}
	//
	int shl = 0;
	set< pair<int, int> >::iterator it, tit;
	for (int pos = 1; pos <= N; pos++)
	{
		printf("%d\n", mi);
		it = R.begin();
		while (!R.empty())
		{
			if (it->first - shl > 0) break;
			L.insert(make_pair(0 - shl, it->second));
			E[it->second] = 0 - shl;
			tit = it;
			it++;
			R.erase(tit);
		}
        L.erase(make_pair(E[Sb[pos]], Sb[pos]));
		R.insert(make_pair(N - P[Sb[pos]] + shl + 1, Sb[pos]));
		E[Sb[pos]] = N - P[Sb[pos]] + shl + 1;
		shl++;
		/*
		cout << shl << endl;
		for (it = L.begin(); it != L.end(); it++)
			cout << it->first << " " << it->second << endl;
        cout << endl;
		for (it = R.begin(); it != R.end(); it++)
			cout << it->first << " " << it->second << endl;
		cout << endl << endl;
        */
        mi = MAXN << 2;
		if (!L.empty()) mi = min(mi, L.begin()->first + shl);
		if (!R.empty()) mi = min(mi, R.begin()->first - shl);
	}
	return 0;
}
