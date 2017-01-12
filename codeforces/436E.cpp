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

/*
1. 最终获得的星星数应恰好为w个，不会超过w。因为，如果每个level只选择1个，则恰为w个，
   如果有level选择了2个同时超过了w，则某些level一定可以只取一个而结果更优。
2. 单调队列+贪婪算法。分别将ai和bi从小到大排序，每次可选择从ai中分别取出2个level的1个星星，也可选
   择从bi中取出1个level的2个星星，保证在取得星星数量相同的情况下选择时间最短的方案。最后还需要维护
   两个单调队列。

*/
using namespace std;
#define LL long long
#define MAXN 300010
typedef set< pair<int, int> >::iterator IT;
int N, w, Q[MAXN], Ea[MAXN], Eb[MAXN];
LL sum;
set< pair<int, int> > Sa, Sb;
IT x, y, z;
void pick_sa(IT it)
{
	int a = it->first;
	int b = it->second;
	sum += a, Q[b]++;
	Sa.erase(it);
	if (Q[b] == 1)
	{
		Sa.insert(make_pair(Eb[b] - Ea[b], b));
		Sb.erase(make_pair(Eb[b], b));
	}
}
void pick_sb(IT it)
{
	int a = it->first;
	int b = it->second;
	sum += a, Q[b] = 2;
	Sb.erase(it);
	Sa.erase(make_pair(Ea[b], b));
}
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &w);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d", &Ea[i], &Eb[i]);
		Sa.insert(make_pair(Ea[i], i));
		Sb.insert(make_pair(Eb[i], i));
	}
	memset(Q, 0, sizeof(Q));
	sum = 0LL;
	while (w > 0)
	{
		if (!(w & 1) && Sa.size() > 1 && Sb.size())
		{
			x = Sa.begin();
			y = ++Sa.begin();
			z = Sb.begin();
			w -= 2;
			if (x->first + y->first < z->first)
			{
				pick_sa(x);
				pick_sa(y);
			}
			else
			{
				pick_sb(z);
			}
		}
		else
		{
			x = Sa.begin();
			pick_sa(x);
			w--;
		}
	}
	cout << sum << endl;
	for (int i = 1; i <= N; i++)
		printf("%d", Q[i]);
	cout << endl;
	return 0;
}
