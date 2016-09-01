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

int N, M;
int E[20][20], C[20];
int em, en;
void init()
{
	char S[20];
	scanf("%d%d", &N, &M);
	memset(E, 0, sizeof(E));
	for (int i = 1; i <= N; i++)
	{
		scanf("%s", S + 1);
		for (int j = 1; j <= M; j++)
			if (S[j] == '.')
			{
				E[i][j] = 1;
				en = i, em = j;
			}
	}
	C[0] = 1;
	for (int i = 1; i <= 20; i++)
		C[i] = C[i - 1] << 1;
	return;
}
int t, ans;
map<int, int> S[2];
map<int, int>::iterator it;
void Hash(int m, int s)
{
    if(S[t].count(m)) S[t][m] += s;
    else S[t][m] = s;
}
void solve()
{
	ans = 0;
	t = 0;
	int tm;
	Hash(0, 1);
	for (int i = 1; i <= N; i++)
    {
		for (int j = 1; j <= M; j++)
		{
			t = 1 - t;
			S[t].clear();
			for (it = S[1 - t].begin(); it != S[1 - t].end(); it++)
			{
				int m = it->first;
				int s = it->second;
				int p = (m >> C[j - 1]) % 4;
				int q = (m >> C[j]) % 4;
				if(j == 1)
                {
                    p = (m << 2 >> C[j - 1]) % 4;
                    q = (m << 2 >> C[j]) % 4;
                }
                cout << m << " " << s << endl;
				if (!E[i][j])
				{
					if (p == 0 && q == 0) Hash(m, s);
				}
				else
				{
					if (p == 0 && q == 0)
					{
						if (E[i][j + 1] && E[i + 1][j])
						{
							tm = m + 1 * (1 << C[j - 1]) + 2 * (1 << C[j]);
							Hash(tm, s);
						}
						continue;
					}
					if (p == 0 && q > 0)
					{
						if (E[i][j + 1]) Hash(tm, s);
						if (E[i + 1][j])
						{
							tm = m - q * (1 << C[j]) + q * (1 << C[j - 1]);
							Hash(tm, s);
						}
						continue;
					}
					if (p > 0 && q == 0)
					{
						if (E[i + 1][j]) Hash(tm, s);
						if (E[i][j + 1])
						{
							tm = m - p * (1 << C[j - 1]) + p * (1 << C[j]);
							Hash(tm, s);
						}
						continue;
					}
					if (p == 1 && q == 1)
					{
						int cnt = 1;
						for (int k = j + 1; k <= N; k++)
						{
							int w = (m >> C[k]) % 4;
							if (w == 1) cnt++;
							if (w == 2) cnt--;
							if (cnt == 0)
							{
								tm = m - 2 * (1 << C[k]) + 1 * (1 << C[k]);
								break;
							}
						}
						tm = tm - 1 * (1 << C[j]) - 1 * (1 << C[j - 1]);
						Hash(tm, s);
						continue;
					}
					if (p == 2 && q == 2)
					{
						int cnt = 1;
						for (int k = j - 2; k >= 1; k--)
						{
							int w = (m >> C[k]) % 4;
							if (w == 2) cnt++;
							if (w == 1) cnt--;
							if (cnt == 0)
							{
								tm = m - 1 * (1 << C[k]) + 2 * (1 << C[k]);
								break;
							}
						}
						tm = tm - 2 * (1 << C[j]) - 2 * (1 << C[j - 1]);
						Hash(tm, s);
						continue;
					}
					if (p == 2 && q == 1)
					{
						tm = m - 2 * (1 << C[j - 1]) - 1 * (1 << C[j]);
						Hash(tm, s);
						continue;
					}
					if (p == 1 && q == 2)
					{
						if (i == en && j == em) ans += s;
						continue;
					}
				}
			}
		}
		cout << endl;
    }
}
int main()
{
	freopen("input.txt", "r", stdin);
	init();
	solve();
	printf("%d\n", ans);
	return 0;
}
