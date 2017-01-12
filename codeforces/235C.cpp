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
struct SAM
{
	struct NODE
	{
		NODE *son[26], *fa;
		int len, flag, cnt;
		int nn;
	};
	NODE *root, T[MAXN << 1], *last, *cur, *B[MAXN << 1];
	int cnt, num[MAXN];
	void init()
	{
		cnt = 0;
		root = last = &T[0];
		memset(T, 0, sizeof(T));
		memset(num, 0, sizeof(num));
	}
	void extend(int x)
	{
		NODE *p = &T[++cnt], *jp = last;
		p->nn = cnt;
		p->len = jp->len + 1;
		last = p;
		for (; jp && !jp->son[x]; jp = jp->fa)
			jp->son[x] = p;
		if (!jp)
			p->fa = root;
		else
		{
			if (jp->len + 1 == jp->son[x]->len)
				p->fa = jp->son[x];
			else
			{
				NODE *r = &T[++cnt], *q = jp->son[x];
				*r = *q;
				r->nn = cnt;
				r->len = jp->len + 1;
				p->fa = q->fa = r;
				for (; jp && jp->son[x] == q; jp = jp->fa) jp->son[x] = r;
			}
		}
	}

	void build(char *S)
	{
		// Õÿ∆À≈≈–Ú
		int ll = strlen(S);
		for (int i = 0; i < ll; i++) extend(S[i] - 'a');
		for (int i = 0; i <= cnt; i++) num[T[i].len]++;
		for (int i = 1; i <= ll; i++) num[i] += num[i - 1];
		for (int i = 0; i <= cnt; i++) B[--num[T[i].len]] = &T[i];
		cur = root;
		for (int i = 0; i < ll; i++)
		{
			cur = cur->son[S[i] - 'a'];
			cur->cnt++;
		}

		for (int i = cnt; i > 0; i--)
		{
			B[i]->fa->cnt += B[i]->cnt;
			B[i]->flag = 0;
		}
		cout << endl;
		for (int i = 0; i <= cnt; i++)
		{
			cout << i << " " << T[i].cnt << endl;
		}
		cout << endl;
	}
} sam;
char S[MAXN], E[MAXN];
int N;
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%s", S);
	sam.init();
	sam.build(S);

	for (int i = 0; i <= sam.cnt; i++)
	{
		cout << sam.B[i]->nn << endl;
	}
	/*
	for (int k = 0; k < strlen(S); k++)
	{
		sam.extend(S[k] - 'a');
		cout << "k = " << k << " " << S[k] << endl;
		for (int i = 0; i <= sam.cnt; i++)
		{
			// cout << i << " " << sam.T[i].len << " " << sam.T[i].nn << endl;
			if (sam.T[i].fa) cout << sam.T[i].nn << " " << sam.T[i].fa->nn << endl;
			else cout << sam.T[i].nn << " " << -1 << endl;

			for (int j = 0; j < 26; j++)
				if (sam.T[i].son[j])
					cout << (char)(j + 'a') << " " << sam.T[i].son[j]->nn << endl;
			cout << endl;

		}
		cout << endl;
	}
	*/

	/*
	scanf("%d", &N);
	for (int k = 1; k <= N; k++)
	{
		scanf("%s", E);
		int ll = strlen(E), ret = 0;
		long long ans = 0;
		sam.cur = sam.root;
		for (int i = 0; i < 2 * ll; i++)
		{
			int x = i >= ll ? E[i - ll] - 'a' : E[i] - 'a';
			if (sam.cur->son[x])
			{
				sam.cur = sam.cur->son[x];
				ret++;
			}
			else
			{
				while (sam.cur && !sam.cur->son[x])
					sam.cur = sam.cur->fa;
				if (!sam.cur)
					sam.cur = sam.root, ret = 0;
				else
				{
					ret = sam.cur->len + 1;     /// ?
					sam.cur = sam.cur->son[x];
				}
			}
			while (sam.cur->fa && sam.cur->fa->len >= ll)
			{
				sam.cur = sam.cur->fa;
				ret = sam.cur->len;
			}
			if (ret >= ll && sam.cur->flag != k)
			{
				sam.cur->flag = k;
				ans = ans + sam.cur->cnt;
			}
		}
		cout << ans << endl;
	}
	*/
	return 0;
}
