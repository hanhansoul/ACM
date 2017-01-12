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
#define MAXN 310

using namespace std;
int N, M, T, E[MAXN][MAXN];
int tp, tu, td;
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d%d%d", &N, &M, &T, &tp, &tu, &td);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &E[i][j]);

	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
        {
            int up, down;
            up = down = 0;
            for (int j = 1; j <= M; j++)
			{

			}
        }

	return 0;
}
