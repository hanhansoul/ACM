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
int C[MAXN], D[MAXN], S[MAXN];
vector< pair<int, int> > R;
struct SEG
{
	bool cov;
	int h;
	int mx, prev, nn;
	// mx当前节点具有的最长序列长度，整棵树有效；
	// nn为具有最长长度为mx的节点号，整棵树有效；
	// prev为当前节点的前一个节点，仅叶节点有效。
} E[MAXN << 2];
void push_up(int rt)
{
	int ll = rt << 1, rr = rt << 1 | 1;
	E[rt].cov = E[ll].cov && E[rr].cov;
	// if(E[rt].mx > max(E[ll].mx, E[rr].mx)) return;
	// return;
	if (E[ll].mx > E[rr].mx) E[rt].mx = E[ll].mx, E[rt].nn = E[ll].nn;
	else E[rt].mx = E[rr].mx, E[rt].nn = E[rr].nn;
}
void push_down(int rt)
{
	int ll = rt << 1, rr = rt << 1 | 1;
	if (!E[ll].cov && E[rt].mx > E[ll].mx) E[ll].mx = E[rt].mx, E[ll].prev = E[rt].prev;
	if (!E[rr].cov && E[rt].mx > E[rr].mx) E[rr].mx = E[rt].mx, E[rr].prev = E[rt].prev;
}
void build(int rt, int l, int r)
{
	if (l == r)
	{
		E[rt].cov = false;
		E[rt].mx = 1;
		E[rt].h = R[l - 1].first;
		E[rt].prev = E[rt].nn = R[l - 1].second;
		return;
	}
	int mid = (l + r) >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	push_up(rt);
	return;
}
void add(int rt, int l, int r, int ll, int rr, int x)
{
	int val = D[x] + 1;
	if (r < ll || l > rr || E[rt].cov) return;
	if (ll <= l && r <= rr)
	{
		if (!E[rt].cov && E[rt].mx < val)
			E[rt].mx = val, E[rt].prev = x;
		return;
	}
	int mid = (l + r) >> 1;
	push_down(rt);
	add(rt << 1, l, mid, ll, rr, x);
	add(rt << 1 | 1, mid + 1, r, ll, rr, x);
	push_up(rt);
	return;
}
void cover(int rt, int l, int r, int pos)
{
	if (pos > r || pos < l) return;
	if (l == r)
	{
		E[rt].cov = true;
		D[E[rt].nn] = E[rt].mx;
		return;
	}
	int mid = (l + r) >> 1;
	push_down(rt);
	cover(rt << 1, l, mid, pos);
	cover(rt << 1 | 1, mid + 1, r, pos);
	push_up(rt);
	return;
}
int query(int rt, int l, int r, int pos)
{
	if (pos > r || pos < l) return 0;
	if (l == r) return rt;
	int mid = (l + r) >> 1;
	push_down(rt);
	if (pos <= mid) return query(rt << 1, l, mid, pos);
	else return query(rt << 1 | 1, mid + 1, r, pos);
}
int maxh;
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	maxh = 0;
	for (int i = 1; i <= N; i++)
	{
		int x;
		scanf("%d", &x);
		maxh = max(maxh, x);
		C[i] = x;
		D[i] = 1;                       // 以元素i开始的最长序列
		R.push_back(make_pair(x, i));

	}
	sort(R.begin(), R.end());
	for (int i = 0; i < R.size(); i++)
	{
		// C[R[i].second] = R[i].first;    // 元素i对应的有序序列中的高度
		S[R[i].second] = i + 1;         // 元素i对应的有序序列位置
	}
	memset(E, 0, sizeof(E));
	build(1, 1, N);

	vector< pair<int, int> >::iterator it;
	for (int i = 0; i < R.size(); i++)
		cout << R[i].first << " " << R[i].second << endl;
	cout << endl;
	for (int i = N; i > 0; i--)
	{
		int h = C[i];
		int low = max(0, h - M);
		//cout << p << " ";
		if (low != 0)
		{
			it = lower_bound(R.begin(), R.end(), make_pair(low, MAXN));
			if (it != R.begin())
			{
				it--;
				add(1, 1, N, 1, it - R.begin() + 1, i);
				//cout << it->second;
			}
		}
		int top = min(maxh + 1, h + M);
		if (top <= maxh)
		{
			it = lower_bound(R.begin(), R.end(), make_pair(top, 0));
			if (it != R.end())
			{
				add(1, 1, N, it - R.begin() + 1, N, i);
				//cout << " " << it->second;
			}
		}
		// cout << endl;
		// cout << low << " " << top << endl;
		cover(1, 1, N, it->second);
		cout << h << endl;
		for (int j = 1; j <= N; j++)
		{
			int s = query(1, 1, N, S[j]);
			cout << C[j] << " " << E[s].mx << " " << endl;
		}
		cout << endl;
		// cout << D[i] << endl;
	}
	cout << E[1].mx << endl;
	return 0;
}
