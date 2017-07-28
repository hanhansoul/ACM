#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
using namespace std;
#define EPS 1e-10
typedef long long ll;
const int maxn = (1 << 20) + 10;
const int INF = 1e9 ;
const double eps = 1e-8;
const int mod = 2520;
ll f[maxn], bin[60];
double dp[maxn];
int n;
char ss[55][25];
int cal(ll u)
{
	int cnt = 0;
	while (u > 0)
	{
		if (u % 2 == 1) cnt++;
		u /= 2;
	}
	return cnt;
}
int main()
{
    freopen("input.txt", "r", stdin);
	cin >> n;
	// for(int i = 1;i <= 20;i++)
	if (n == 1)
	{
		cout << 0.000000000 << endl;
		return 0;
	}
	for (int i = 0; i < n; i++)
		scanf("%s", ss[i]);
	bin[0] = 1;
	for (int i = 1; i <= 50; i++) bin[i] = bin[i - 1] * 2;
	int m = strlen(ss[0]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				int same = 0;
				for (int k = 0; k < m; k++)
					if (ss[i][k] == ss[j][k])
						same |= (bin[k]);
				f[same] |= (bin[j]);
			}
		}
	//cout<<(1<<40)<<endl;
	int se = (1 << m) - 1;
	for (int i = se; i >= 0; i--)
	{
		for (int j = 0; j < m; j++)
			if (i & bin[j])
				f[i ^ bin[j]] |= f[i];
	}
	f[0] = bin[n] - 1;
	//for(int i = 0;i <= se;i++)
    //    cout<<i<<" "<<f[i]<<endl;
	double res = 0.0;
	dp[0] = 1.0;
	for (int i = 0; i <= se; i++)
	{
		double cnt = m - cal((ll)i) + 1;
        cout << cnt << endl;
		for (int j = 0; j < m; j++)
		{
			if ((i & bin[j]) && f[i ^ bin[j]] > 0)
			{
				// double cnt1 = cal(f[i^bin[j]]);
				dp[i] += dp[i ^ bin[j]] * (1.0 / cnt);
			}
		}
		//cout<<i<<" "<<dp[i]<<endl;
	}
	for(int i = 0;i <= se;i++)
        cout<<i<<" "<<dp[i]<<endl;

	for (int i = 0; i <= se; i++)
	{
		for (int j = 0; j < n; j++)
			if (f[i]&bin[j])
				res += dp[i];
        cout << res << endl;
	}

	printf("%.10f\n", res / n);
	return 0;
}
