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
const int Limitn = 15;
const int Limithash = 1999997;
int a[Limitn][Limitn];  //地图，判断线段可放不
int k, n, m, nn, mm;    //k：滚动用。
int jz[Limitn];         //进制移动的位数
int hash[Limithash];    //hash里存的东东是当前状态在state里第几个位置
unsigned long long state[2][600000], sum[2][600000]; //state状态，sum:该状态的和
int total[2];           //该格子状态的总数
int ans = 0;
void init()
{
	char ch;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%c", &ch);
		for (int j = 1; j <= m; j++)
		{
			scanf("%c", &ch);
			a[i][j] = ch == '.';
			if (ch == '.')
			{
				nn = i;    //nn,mm记录的是最后一个可覆盖线段的格子的位置
				mm = j;
			}
		}
	}
}
void prepared_jinzhi()
{
	jz[0] = 0;
	for (int i = 1; i <= n; i++)
		jz[i] = i << 1;
}
void Hash_in(unsigned long long s, int data) //哈希
{
	int hashpos = s % Limithash;
	while (hash[hashpos])
	{
		if (state[k][hash[hashpos]] == s) //如果状态存在
		{
			sum[k][hash[hashpos]] += data;
			return;
		}
		hashpos++;
		if (hashpos == Limithash) hashpos = 0;
	}
	total[k]++;//新状态
	hash[hashpos] = total[k];
	state[k][total[k]] = s;
	sum[k][total[k]] = data;
}
void work()
{
	int tmps;
	total[0] = 1;
	sum[0][1] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			k ^= 1;                             //滚动
			memset(hash, 0, sizeof(hash));
			memset(sum[k], 0, sizeof(sum[k]));
			memset(state[k], 0, sizeof(state[k]));
			total[k] = 0;                       //清空滚动数组上次的记录
			for (int u = 1; u <= total[1 - k]; u++) //对于前一格每个有效的状态分别扩展
			{
				int s = state[1 - k][u];        //取出状态
				int data = sum[1 - k][u];       //到达前一格该状态下的方案总数
				int p = (s >> jz[j - 1]) % 4;   //取第j-1位的括号
				int q = (s >> jz[j]) % 4;       //取第j位的括号
				if (!a[i][j])                   //如果不能覆盖线段
				{
					if (p == 0 && q == 0) Hash_in(s, data); //如果连线可以绕开障碍，则新增该状态。
				}
				else                            //如果能覆盖线段
				{
					if (p == 0 && q == 0)
					{
						if (a[i][j + 1] && a[i + 1][j])
						{
							tmps = s + 1 * (1 << jz[j - 1]) + 2 * (1 << jz[j]);
							Hash_in(tmps, data);
						}
						continue;
					}
					if (p == 0 && q > 0)
					{
						if (a[i][j + 1])
							Hash_in(s, data);
						if (a[i + 1][j])
						{
							tmps = s - q * (1 << jz[j]);
							tmps += q * (1 << jz[j - 1]);
							Hash_in(tmps, data);
						}
						continue;
					}
					if (p > 0 && q == 0)
					{
						if (a[i + 1][j])
							Hash_in(s, data);
						if (a[i][j + 1])
						{
							tmps = s - p * (1 << jz[j - 1]);
							tmps += p * (1 << jz[j]);
							Hash_in(tmps, data);
						}
						continue;
					}
					if (p == 1 && q == 1)
					{
						int brackets = 1; //寻找匹配的括号
						for (int v = j + 1; v <= n; v++)
						{
							int w = (s >> jz[v]) % 4;
							if (w == 1) brackets++;
							if (w == 2) brackets--;
							if (brackets == 0)
							{
								tmps = s - 2 * (1 << jz[v]) + 1 * (1 << jz[v]);
								break;
							}
						}
						tmps = tmps - 1 * (1 << jz[j - 1]) - 1 * (1 << jz[j]);
						Hash_in(tmps, data);
						continue;
					}
					if (p == 2 && q == 2)
					{
						int brackets = 1;
						for (int v = j - 2; v >= 1; v--)
						{
							int w = (s >> jz[v]) % 4;
							if (w == 2) brackets++;
							if (w == 1) brackets--;
							if (brackets == 0)
							{
								tmps = s - 1 * (1 << jz[v]) + 2 * (1 << jz[v]);
								break;
							}
						}
						tmps = tmps - 2 * (1 << jz[j - 1]) - 2 * (1 << jz[j]);
						Hash_in(tmps, data);
						continue;
					}
					if (p == 2 && q == 1)
					{
						tmps = s - 2 * (1 << jz[j - 1]) - 1 * (1 << jz[j]);
						Hash_in(tmps, data);
						continue;
					}
					if (p == 1 && q == 2)
					{
						if (i == nn && j == mm) ans += data;
						continue;
					}
				}
			}
		}
		for (int i = 1; i <= total[k]; i++)                 //每一行做完后，应该乘以4，这个用笔算下，就很清楚了
			state[k][i] = state[k][i] << 2;
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	init();
	prepared_jinzhi();
	work();
	printf("%d\n", ans);
	return 0;
}
