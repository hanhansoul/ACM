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

int N, M, S[100];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++)
		scanf("%d", &S[i]);
	sort(S + 1, S + M + 1);
	int ans = 0x3f3f3f3f;
	for (int i = 1, j = 1 + N - 1; j <= M; i++, j++)
		ans = min(ans, S[j] - S[i]);
	printf("%d\n", ans);
	return 0;
}
