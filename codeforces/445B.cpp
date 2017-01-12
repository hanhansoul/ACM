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

int N, M;
char S[MAXN];
struct NODE
{
	int son[30];
} T[MAXN];
int tot;
void Insert(char* S)
{
	int k = 0, rt = 1;
	while (S[k])
	{
		int t = S[k] - 'a';
		if (T[rt].son[t] == 0)
			T[rt].son[t] = ++tot;
		rt = T[rt].son[t];
		k++;
	}
}
int dfs(int rt)
{
	int res, s = 0;
	bool d0, d1;
	d0 = d1 = false;
	for (int i = 0; i < 26; i++)
		if (T[rt].son[i])
			s |= dfs(T[rt].son[i]);
    if(s == 0) res = 1;
    else if(s == (1 << 0)) res = (1 << 1);
    else if(s == (1 << 2)) res = (1 << 3);
    else if(s & (1 << 3)) res = (1 << 2);
    else if(s & (1 << 0)) res = (1 << 1);
	return res;
}
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	tot = 1;
	memset(T, 0, sizeof(T));
	for (int i = 1; i <= N; i++)
	{
		scanf("%s", S);
		Insert(S);
	}
	dfs(1);
	return 0;
}
