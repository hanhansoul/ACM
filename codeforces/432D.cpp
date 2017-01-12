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

struct SAM
{
	int val[MAXN << 1], fa[MAXN << 1], son[MAXN << 1][30];
	int tot, last;
	inline int newNode(int v)
	{
		val[++tot] = v;
		fa[tot] = 0;
		for (int i = 0; i < 30; i++)
			son[tot][i] = 0;
		return tot;
	}
	inline void extend(int k)
	{
		int p = last;
		int np = newNode(val[last] + 1);
		for (; p && !son[p][k]; p = fa[p]) son[p][k] = np;
		if (!p)
			fa[np] = 1;
		else
		{
			int q = son[p][k];
			if (val[q] == val[p] + 1)
				fa[np] = q;
			else
			{
				int nq = newNode(val[p] + 1);
				for (int i = 0; i < 30; i++)
					son[nq][i] = son[q][i];
				fa[nq] = fa[q];
				fa[q] = fa[np] = nq;
				for (; p && son[p][k] == q; p = fa[p]) son[p][k] = nq;
			}
		}
		last = np;
	}
	inline void init()
	{
		tot = 0;
		last = newNode(0);
	}
} sam;

char S[MAXN];

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%s", S);
	int len = strlen(S);
	int ph,pt;
	ph = 0, pt =
	for(int i=0;i<len;i++)
    {

    }
	return 0;
}
