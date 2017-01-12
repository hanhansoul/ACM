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

int N, Sa[110];
int P[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
int R[65];
int D[110][(1 << 16)], Q[110][(1 << 16)][2];
void print(int r, int msk)
{
	if (r == 0) return;
	print(r - 1, Q[r][msk][1]);
	printf("%d ", Q[r][msk][0]);
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &Sa[i]);
	for (int i = 1; i < 60; i++)
		for (int j = 0; j < 16; j++)
		{
			if (P[j] > i) break;
			if (i % P[j] == 0) R[i] |= (1 << j);
		}
	memset(D, 0x3f, sizeof(D));
	D[0][0] = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < (1 << 16); j++)
			for (int k = 1; k < 60; k++)
				if (!(j & R[k]) && D[i][j | R[k]] > D[i - 1][j] + abs(Sa[i] - k))
				{
					D[i][j | R[k]] = D[i - 1][j] + abs(Sa[i] - k);
					Q[i][j | R[k]][0] = k;
					Q[i][j | R[k]][1] = j;
				}
	int mi = 0x3f3f3f3f, st;
	for (int i = 0; i < (1 << 16); i++)
		if (mi > D[N][i])
		{
			mi = D[N][i];
			st = i;
		}
    // cout << mi << endl;
	print(N, st);
	return 0;
}
