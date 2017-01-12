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
#define MAXN 2010
#define MOD 1000000007
#define LL long long
int N;
LL S[MAXN], h;

int main()
{
	// freopen("input.txt", "r", stdin);
	cin >> N >> h;
	for (int i = 1; i <= N; i++)
	{
		cin >> S[i];
		S[i] = h - S[i];
	}
	S[0] = 0;
	LL ans = 1LL;
	int cnt = 0;
	for (int i = 1; i <= N + 1; i++)
	{
		LL dh = S[i] - S[i - 1];
		if (dh > 1 || dh < -1)
		{
			ans = 0LL;
			break;
		}
		else if (dh == 1)
			cnt++;
		else if (dh == 0)
			ans = ans * (cnt + 1) % MOD;
		else if (dh = -1)
			ans = ans * cnt % MOD, cnt--;
	}
	cout << ans << endl;
	return 0;
}
