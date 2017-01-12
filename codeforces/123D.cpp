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

char S[MAXN];
struct SAM
{
	struct NODE
	{
		NODE *son[26], *fa;
		int len;        // len��ʾ��ǰ�ڵ��¼�Ӵ��������
		int cnt;
	};
	NODE T[MAXN << 1];
	NODE *root, *last, *cur;
	int tot;            // �ڵ�����
	NODE *B[MAXN << 1]; // ������������
	int E[MAXN];        // ������������
	void init()
	{
		tot = 0;
		root = last = &T[0];
		memset(T, 0, sizeof(T));
		memset(E, 0, sizeof(E));
	}

	void extend(int x)
	{
		NODE *p = &T[++tot], *jp = last;
		p->len = jp->len + 1, last = p;
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
				NODE *r = &T[++tot], *q = jp->son[x];
				*r = *q;
				r->len = jp->len + 1;
				p->fa = q->fa = r;
				for (; jp && jp->son[x] == q; jp = jp->fa)
					jp->son[x] = r;
			}
		}
	}

	void build(char *S)
	{
		// ��������
		int ll = strlen(S);
		for (int i = 0; i < ll; i++) extend(S[i] - 'a');
		for (int i = 0; i <= tot; i++) E[T[i].len]++;
		for (int i = 1; i <= ll; i++) E[i] += E[i - 1];
		for (int i = 0; i <= tot; i++) B[--E[T[i].len]] = &T[i];
		// ����ÿ���ڵ��������Ӵ���ĸ���г��ֵĴ���
		cur = root;
		for (int i = 0; i < ll; i++)
		{
			cur = cur->son[S[i] - 'a'];
			cur->cnt++;
		}
		for (int i = tot; i > 0; i--)
			B[i]->fa->cnt += B[i]->cnt;
	}
} sam;
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%s", S);
	sam.init();
	sam.build(S);
	LL ans = 0LL;
	for (int i = 1; i <= sam.tot; i++)
    {
        int t = sam.T[i].len - sam.T[i].fa->len;
        ans += 1LL * t * sam.T[i].cnt * (sam.T[i].cnt + 1) / 2;
    }
	cout << ans << endl;
	return 0;
}
