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
#define MAXN 45

int N, S[5][5];
int F[MAXN][MAXN];
int dfs(int tot, int x, int y)
{
    if(tot==1)
    {
        return;
    }

}
int main()
{
	freopen("input.txt", "r", stdin);
	for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            scanf("%d", &S[i][j]);
    scanf("%d", &N);

	return 0;
}
