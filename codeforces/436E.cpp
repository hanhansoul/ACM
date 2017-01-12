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
1. ���ջ�õ�������Ӧǡ��Ϊw�������ᳬ��w����Ϊ�����ÿ��levelֻѡ��1������ǡΪw����
   �����levelѡ����2��ͬʱ������w����ĳЩlevelһ������ֻȡһ����������š�
2. ��������+̰���㷨���ֱ�ai��bi��С��������ÿ�ο�ѡ���ai�зֱ�ȡ��2��level��1�����ǣ�Ҳ��ѡ
   ���bi��ȡ��1��level��2�����ǣ���֤��ȡ������������ͬ�������ѡ��ʱ����̵ķ����������Ҫά��
   �����������С�

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
