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

int M;
char S[15];
bool E[15], F[1010][15][25];
vector<int> R;
pair<int, int> P[1010][15][25];
int ax, ay;
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%s", S + 1);
	scanf("%d", &M);
	for (int i = 1; i <= strlen(S + 1); i++)
		if (S[i] == '0') E[i] = false;
		else E[i] = true;
    // solve
	memset(F, false, sizeof(F));
	for (int i = 1; i <= 10; i++)
		F[1][i][10 + i] = E[i];
	for (int i = 2; i <= M; i++)
		for (int j = 1; j <= 10; j++)
		{
			if (!E[j]) continue;
			if (i & 1)
			{
				for (int k = 1; k < 10; k++)
				{
					if (!F[i - 1][j][k]) continue;
					for (int d = 1; d <= 10; d++)
						if (E[d] && d != j && 10 < k + d && k + d <= 20)
						{
							F[i][d][k + d] = true;
							P[i][d][k + d] = make_pair(j, k);
						}
				}
			}
			else
			{
				for (int k = 11; k < 20; k++)
				{
					if (!F[i - 1][j][k]) continue;
					for (int d = 1; d <= 10; d++)
						if (E[d] && d != j && 0 <= k - d && k - d < 10)
						{
							F[i][d][k - d] = true;
							P[i][d][k - d] = make_pair(j, k);
						}
				}
			}
		}
    // output
    ax = ay = -1;
	for (int i = 1; i <= 10; i++)
	{
		if (!E[i]) continue;
		for (int j = 0; j <= 20; j++)
			if (F[M][i][j])
				ax = i, ay = j;
	}
	if (ax == -1 && ay == -1)
		printf("NO\n");
	else
	{
		printf("YES\n");
		for (int i = M; i >= 1; i--)
		{
			int xx = P[i][ax][ay].first;
			int yy = P[i][ax][ay].second;
			R.push_back(ax);
			ax = xx, ay = yy;
		}
		for (int i = R.size() - 1; i >= 0; i--)
			printf("%d ", R[i]);
		printf("\n");
	}
	return 0;
}
