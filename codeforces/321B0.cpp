#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
#include <cmath>
#include <set>
#include <vector>
using namespace std;
template <class T>
inline bool rd(T &ret)
{
	char c;
	int sgn;
	if (c = getchar(), c == EOF) return 0;
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	sgn = (c == '-') ? -1 : 1;
	ret = (c == '-') ? 0 : (c - '0');
	while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
	ret *= sgn;
	return 1;
}
template <class T>
inline void pt(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9) pt(x / 10);
	putchar(x % 10 + '0');
}
typedef long long ll;
typedef pair<int, int> pii;
const int inf = 1e9;
const int INF = 1e6;
const int N = 205;
const int M = 205;
int n, m;
int a[N], b[N];
bool p[N];
int nx, ny;
int link[M], lx[M], ly[M], slack[M];    //lx,lyΪ���꣬nx,ny�ֱ�Ϊx�㼯y�㼯�ĸ���
int visx[M], visy[M], w[M][M];

int DFS(int x)
{
	visx[x] = 1;
	for (int y = 1; y <= ny; y++)
	{
		if (visy[y])
			continue;
		int t = lx[x] + ly[y] - w[x][y];
		if (t == 0)       //
		{
			visy[y] = 1;
			if (link[y] == -1 || DFS(link[y]))
			{
				link[y] = x;
				return 1;
			}
		}
		else if (slack[y] > t)  //���������ͼ��slack ȡ��С��
			slack[y] = t;
	}
	return 0;
}
int KM()
{
	int i, j;
	memset(link, -1, sizeof(link));
	memset(ly, 0, sizeof(ly));
	for (i = 1; i <= nx; i++)          //lx��ʼ��Ϊ����������������
		for (j = 1, lx[i] = -inf; j <= ny; j++)
			if (w[i][j] > lx[i])
				lx[i] = w[i][j];

	for (int x = 1; x <= nx; x++)
	{
		for (i = 1; i <= ny; i++)
			slack[i] = inf;
		while (1)
		{
			memset(visx, 0, sizeof(visx));
			memset(visy, 0, sizeof(visy));
			if (DFS(x))     //���ɹ����ҵ�������죩����õ�������ɣ�������һ���������
				break;  //��ʧ�ܣ�û���ҵ�����죩������Ҫ�ı�һЩ��ı�ţ�ʹ��ͼ�п��бߵ��������ӡ�
			//����Ϊ����������������У���������������б���������X����ı��ȫ����ȥһ������d��
			//������������е�Y����ı��ȫ������һ������d
			int d = inf;
			for (i = 1; i <= ny; i++)
				if (!visy[i] && d > slack[i])
					d = slack[i];
            // cout << i << " " << d << endl;
			for (i = 1; i <= nx; i++)
				if (visx[i])
					lx[i] -= d;
			for (i = 1; i <= ny; i++) //�޸Ķ����Ҫ�����в��ڽ������е�Y�����slackֵ����ȥd
				if (visy[i])
					ly[i] += d;
				else
					slack[i] -= d;
		}
	}
	int res = 0;
	for (i = 1; i <= ny; i++)
		if (link[i] > -1)
			res += w[link[i]][i];
	return res;
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output0.txt", "w", stdout);
	rd(n);
	rd(m);
	for (int i = 1; i <= n; i++)
	{
		char s[5];
		scanf("%s", s);
		rd(a[i]);
		p[i] = s[0] == 'A';
	}
	for (int i = 1; i <= m; i++) rd(b[i]);

	nx = ny = max(n, m);
	memset(w, 0, sizeof w);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			if (p[j])
			{
				if (b[i] >= a[j])w[i][j] = b[i] - a[j];
			}
		}
    int ans = 0;
	// int ans = KM();
	// cout << ans << endl;

	if (m > n)
	{
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
			{
				if (p[j])
				{
					if (b[i] >= a[j])w[i][j] = b[i] - a[j];
					else w[i][j] = -INF;
				}
				else
				{
					if (b[i] > a[j]) w[i][j] = 0;
					else w[i][j] = -INF;
				}
			}
		for (int i = 1; i <= m; i++)
			for (int j = n + 1; j <= m; j++)
				w[i][j] = b[i];
        /*
		for (int i = 1; i <= nx; i++)
		{
			for (int j = 1; j <= nx; j++)
				cout << w[i][j] << " ";
			cout << endl;
		}
        */
		ans = max(ans, KM());
	}
	pt(ans);
	return 0;
}
