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
#define LL long long
#define MOD 1000000007

int N;
char S1[MAXN], S2[MAXN];
LL F[MAXN], D[3][MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	scanf("%s", S1 + 1);
	scanf("%s", S2 + 1);

	int s = 0;
	for (int i = 0; i < 10; i++)
		for (int j = i + 1; j < 10; j++)
			s++;

	// S2[i] - S1[i]
	memset(F, 0, sizeof(F));
	memset(D, 0, sizeof(D));
	D[2][0] = 1;
	for (int i = 1; i <= N; i++)
	{
		int a = S1[i] == '?' ? (-1) : S1[i] - '0';
		int b = S2[i] == '?' ? (-1) : S2[i] - '0';
		int t0, t1, t2, tf;
		if (a >= 0 && b >= 0)
		{
			tf = 1;
			t0 = t1  = t2 = 0;
			if (a < b) t0 = 1;
			else if (a > b) t1 = 1;
			else if (a == b) t2 = 1;
		}
		else if (a >= 0 && b < 0)
			tf = 10, t0 = 9 - a, t1 = a, t2 = 1;
		else if (a < 0 && b >= 0)
			tf = 10, t0 = b, t1 = 9 - b, t2 = 1;
		else if (a < 0 && b < 0)
			tf = 100, t0 = t1 = s, t2 = 10;

		F[i] = (F[i - 1] * tf % MOD + D[0][i - 1] * t1 % MOD + D[1][i - 1] * t0 % MOD) % MOD;
		D[0][i] = ((D[0][i - 1] + D[2][i - 1]) * t0 % MOD + D[0][i - 1] * t2 % MOD) % MOD;
		D[1][i] = ((D[1][i - 1] + D[2][i - 1]) * t1 % MOD + D[1][i - 1] * t2 % MOD) % MOD;
		D[2][i] = D[2][i - 1] * t2 % MOD;
	}
	cout << F[N] << endl;
	return 0;
}
