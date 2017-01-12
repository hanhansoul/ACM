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
#define INF 0x3f3f3f3f
/*
    D[i][j] ��ʾa����ǰi�b����ǰj�ȡD[i][j]�����֡�
    ���� 1 <= i, j <= 100000��������Χ����Ҫ��״̬��ʾ��ʽ�����޸ġ�
    ע�⵽D[i][j]���Ϊs/e����s/e <= 300����˲���F[i][j]�ı�ʾ״̬��
    F[i][j] ��ʾ��a���е�ǰj���У�ȡi�����֣�ʹ��b����ȡ����λ��ΪF[i][j]��
    ����������������ƣ���ȡ�����ֶ�������ͬ������£�������ȡ���������λ�á�
    F[i][j] = min(F[i - 1][j], pos);
    ����posΪb�����У�ֵΪA[j]����λ�ô���F[i - 1][j - 1] + 1������λ�á�
*/
int N, M, s, e;
int Sa[MAXN], Sb[MAXN];
int F[310][MAXN];
vector<int> P[MAXN];
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &s, &e);
	for (int i = 1; i <= N; i++)
		scanf("%d", &Sa[i]);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d", &Sb[i]);
		P[Sb[i]].push_back(i);
	}
	for (int i = 0; i <= MAXN; i++)
		P[i].push_back(INF);
	memset(F, 0x3f, sizeof(F));
	memset(F[0], 0, sizeof(F[0]));
	int ans = 0;
	for (int i = 1; i <= s / e; i++)
		for (int j = 1; j <= N; j++)
			if (F[i - 1][j - 1] < INF)
			{
				F[i][j] = F[i][j - 1];
				int tmp = *lower_bound(P[Sa[j]].begin(), P[Sa[j]].end(), F[i - 1][j - 1] + 1);
				F[i][j] = min(F[i][j], tmp);
				if (F[i][j] + j + i * e <= s) ans = max(ans, i);
			}

	printf("%d\n", ans);
	return 0;
}
