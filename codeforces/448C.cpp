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
#define MAXN 5010

int N, H[MAXN], D[MAXN][MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &H[i]);

	memset(D, 0x3f, sizeof(D));
	D[0][0] = 0;
	for (int i = 1; i <= N; i++)
		for (int j = i - 1; j >= 0; j--)
		{
			if (H[j] == H[i]) D[i][j] = min(D[i][j], D[i - 1][j]);
			else if (H[j] < H[i]) D[i][j] = min(D[i][j], D[i - 1][j] + 1);

			if (H[j] >= H[i]) D[i][i] = min(D[i][i], D[i - 1][j]);
			else D[i][i] = min(D[i][i], D[i - 1][j] + H[i] - H[j]);
		}
	int ans = 0x3f3f3f3f;
	for(int i=0;i<=N;i++)
        ans = min(ans, D[N][i]);
    printf("%d\n", ans);
	return 0;
}
