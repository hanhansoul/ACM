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
#define INF 0x3f3f3f3f
/*
    D[i][j] 表示a序列前i项，b序列前j项，取D[i][j]对数字。
    由于 1 <= i, j <= 100000，超出范围，需要对状态表示方式进行修改。
    注意到D[i][j]最大为s/e，而s/e <= 300，因此采用F[i][j]的表示状态。
    F[i][j] 表示在a序列的前j项中，取i对数字，使得b序列取数字位置为F[i][j]。
    与最长公共子序列相似，在取得数字对数量相同的情况下，尽可能取序列最左侧位置。
    F[i][j] = min(F[i - 1][j], pos);
    其中pos为b序列中，值为A[j]，且位置大于F[i - 1][j - 1] + 1的最靠左的位置。
*/
int N, M, s, e;
int Sa[MAXN], Sb[MAXN];
int F[310][MAXN];
vector<int> P[MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &s, &e);
	for (int i = 1; i <= N; i++)
		scanf("%d", &Sa[i]);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d", &Sb[i]);
		P[Sb[i]].push_back(i);
	}
	for (int i = 0; i <= MAXN; i++)
		P[i].push_back(INF);
	memset(F, 0x3f, sizeof(F));
	memset(F[0], 0, sizeof(F[0]));
	int ans = 0;
	for (int i = 1; i <= s / e; i++)
		for (int j = 1; j <= N; j++)
			if (F[i - 1][j - 1] < INF)
			{
				F[i][j] = F[i][j - 1];
				int tmp = *lower_bound(P[Sa[j]].begin(), P[Sa[j]].end(), F[i - 1][j - 1] + 1);
				F[i][j] = min(F[i][j], tmp);
				if (F[i][j] + j + i * e <= s) ans = max(ans, i);
			}

	printf("%d\n", ans);
	return 0;
}
