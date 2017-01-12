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

const LL mx = 1000000000000000000LL;
int K;
LL M, C[70][70];

inline LL Count(LL x)
{
	int cnt = 0;
	LL sum = 0LL;
	for (int i = 63; i >= 0; i--)
		if (x & (1LL << i))
		{
			if (K - cnt >= 0) sum += C[i][K - cnt];
			cnt++;
		}
	if (cnt == K) sum++;
	return sum;
}

int main()
{
	// freopen("input.txt", "r", stdin);
	cin >> M >> K;
	C[0][0] = 1;
	for (int i = 1; i <= 65; i++)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}

	LL l, r, mid, ans;
	l = 1, r = mx;
	while (l <= r)
	{
		mid = (l + r) / 2LL;
		LL v = Count(mid * 2) - Count(mid);
		if (v < M) l = mid + 1;
		else r = mid - 1;
	}
	cout << l << endl;
	return 0;
}
