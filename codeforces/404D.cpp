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
#define MAXN 1000010
#define MOD 1000000007
#define LL long long

char S[MAXN];
LL F[MAXN][5];
void convert(LL &x)
{
	while (x >= MOD) x -= MOD;
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%s", S + 1);
	int len = strlen(S + 1);
	memset(F, 0, sizeof(F));
	F[0][0] = F[0][2] = 1LL;
	for (int i = 1; i <= len; i++)
	{
		if (S[i] == '?')
		{
			F[i][0] = F[i - 1][0] + F[i - 1][1];
			F[i][1] = F[i - 1][4];
			F[i][2] = F[i - 1][0] + F[i - 1][1];
			F[i][3] = F[i - 1][4];
			F[i][4] = F[i - 1][2] + F[i - 1][3] + F[i - 1][4];
		}
		else
		{
			if (S[i] == '*')
				F[i][4] = F[i - 1][2] + F[i - 1][3] + F[i - 1][4];
			else if (S[i] == '0')
				F[i][0] = F[i - 1][0] + F[i - 1][1];
			else if (S[i] == '1')
				F[i][1] = F[i - 1][4], F[i][2] = F[i - 1][0] + F[i - 1][1];
			else if (S[i] == '2')
				F[i][3] = F[i - 1][4];
		}
		for (int j = 0; j < 5; j++)
			convert(F[i][j]);
	}
	LL ans = F[len][0] + F[len][1] + F[len][4];
	convert(ans);
	cout << ans << endl;
	return 0;
}
