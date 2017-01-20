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
#define MAXN (1 << 20)
#define LL long long

int N;
string S[55];
//double F[MAXN][55];     // F[msk][i]记录msk下的第i组的期望值。
//int R[MAXN][55];        // R[msk][i]记录msk下的第i组包含的字符串，为一个bit mask。
//int C[MAXN][55];        // C[msk][i]记录msk下的第i组包含的字符串的数量。

// set<char> E[55];

map<int, LL> F[MAXN];
map<int, LL>::iterator it;
map<char, int> E[55];
map<char, int>::const_iterator eit;
LL R[55];
int len;

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		cin >> S[i];
		len = S[i].length();
		for (int j = 0; j < len; j++)
			E[j][S[i][j]] |= (1 << i);
	}

	int full = (1 << N) - 1;
	F[full][0] = 1;
	for (int msk = full; msk >= 0; msk--)
		for (it = F[msk].begin(); it != F[msk].end(); it++)
			for (int p = 0; p < len; p++)
			{
				int v = (1 << p);
				int key = it->first;
				double val = it->second;
				if (key & v) continue;

				for (eit = E[p].begin(); eit != E[p].end(); eit++)
					F[(msk & E[p]->second)][key | v] += val;
			}

	LL tot = 0LL;
	for (int i = 0; i < N; i++)
	{
		int k = (1 << i);
		for (it = F[k].begin(); it != F[k].end(); it++)
		{
			int c = __builtin_popcount(it->first);
			R[c] += F[k]->second;
			tot += F[k]->second;
		}
	}


	return 0;
}
