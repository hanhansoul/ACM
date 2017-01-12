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
#define MAXN 5 * 10010

int N;
char S[MAXN], D[110];
int F[MAXN][110], R[2][110], E[MAXN][110];
vector<int> P[30];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%s", S + 1);
	N = strlen(S + 1);
	for (int i = 1; i <= N; i++)
		P[S[i] - 'a'].push_back(i);
	memset(F, -1, sizeof(F));
	int ax, ay, mx, tmp;
	ax = ay = mx = tmp = 0;
	for (int i = 1; i <= N; i++)
	{
		int ch = S[i] - 'a';
		F[i][1] = E[i][1] = R[1 - tmp][1] = i;
		if(1 > mx) mx = 1, ax = i, ay = mx;
		for (int j = 2; j <= 100; j++)
		{
			F[i][j] = F[i - 1][j];
			R[1 - tmp][j] = R[tmp][j];
			if (F[i][j] != -1) mx = j;
		}
		for (int j = 0; j <= min(100 - 2, i - 2); j++)
		{
			int pos = F[i - 1][j];
			if(j == 0) pos = i;
			// cond: P[ch][index] <= pos - 1
			int index = lower_bound(P[ch].begin(), P[ch].end(), pos) - P[ch].begin() - 1;
			if (index >= 0 && F[i][j + 2] < P[ch][index])
			{
				F[i][j + 2] = P[ch][index];
				E[i][j + 2] = R[tmp][j];
				R[1 - tmp][j + 2] = i;
				if (j + 2 > mx) mx = j + 2, ax = i, ay = mx;
			}
		}
		tmp = 1 - tmp;
		if (mx == 100) break;
	}
	int st = 0, en = mx - 1;
	for (;st <= en;)
	{
		D[st] = D[en] = S[F[ax][ay]];
		ax = E[ax][ay], ay -= 2;
		st++, en--;
	}
	// cout << strlen(D) << endl;
	printf("%s\n", D);
	return 0;
}
