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
#define MAXN 510
#define LL long long

int N;
int E[MAXN][MAXN], D[MAXN][MAXN], T[MAXN];
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            scanf("%d", &E[i][j]);

    for(int i=1;i<=N;i++)
        scanf("%d", &T[i]);

    for(int k=N;k>=1;k--)
    {
        for(int i=N;i>=k;i--)
        {

        }

        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
        {

        }
    }
	return 0;
}
