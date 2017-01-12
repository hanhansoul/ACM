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
#define LL long long
#define MOD 7340033

int N, K, T;
LL F[40][1010], D[1010];
void init()
{
    memset(F, 0, sizeof(F));
    F[0][0] = 1;
	for (int i = 1; i <= 30; i++)
    {
        memset(D, 0, sizeof(D));
		for (int j = 0; j <= 1000; j++)
			for (int k = 0; k <= j; k++)
			{
				D[j] += F[i - 1][k] * F[i - 1][j - k];
				if (D[j] >= MOD) D[j] %= MOD;
			}
		F[i][0] = 1;
		for (int j = 1; j <= 1000; j++)
			for (int k = 0; k < j; k++)
			{
				F[i][j] += D[k] * D[j - k - 1];
				if (F[i][j] >= MOD) F[i][j] %= MOD;
			}
    }
}

void solve(int nn, int kk)
{
    int part = 0;
    while(nn > 1 && nn % 2)
    {
        nn /= 2;
        part++;
    }
    printf("%d\n", F[part][kk]);
}
int main()
{
	// freopen("input.txt", "r", stdin);
	init();
	scanf("%d", &T);
	while(T--)
    {
        scanf("%d%d", &N, &K);
        solve(N, K);
    }
	return 0;
}
