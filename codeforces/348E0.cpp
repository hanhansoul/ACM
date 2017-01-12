#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 100000 + 9;
int n, m, son[N], lnk[N * 2], w[N * 2], nxt[N * 2], dis[N], fir[N], dfn[N], fa[N], tot, ec, f[N];
bool v[N], vis[N];
inline void addedge(int x, int y, int z)
{
	nxt[++ec] = son[x];
	son[x] = ec;
	lnk[ec] = y;
	w[ec] = z;
}
void dfs(int u, int father)
{
	dfn[++tot] = u;
	fa[u] = father;
	if (father && !fa[father]) fir[u] = u;
	else fir[u] = fir[father];
	for (int i = son[u]; i; i = nxt[i])
		if (lnk[i] != father)
		{
			dis[lnk[i]] = dis[u] + w[i];
			dfs(lnk[i], u);
		}
}
int walk(int s)
{
	tot = 0;
	dis[s] = 0;
	dfs(s, 0);
	for (int i = 1; i <= n; ++i)
		if (dis[s] < dis[i] && v[i]) s = i;
	return s;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	// freopen("348E.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	int tmp;
	for (int x, i = 1; i <= m; ++i)
		scanf("%d", &x), v[x] = true, tmp = x;
	for (int i = 1, x, y, z; i < n; ++i)
	{
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
		addedge(y, x, z);
	}
	int s = walk(tmp), t = walk(s), mid, cnt = 0;
	for (mid = fa[t]; dis[mid] > dis[t] / 2; mid = fa[mid]);
	tot = 0;
	dis[mid] = 0;
	dfs(mid, 0);
	/*
	cout << "fir[]" << endl;
	for (int i = 1; i <= n; i++)
		cout << fir[i] << " ";
    cout << endl;
    cout << dis[t] << endl;
    cout << s << " " << t << " " << mid << endl;
    */
    cout << mid << endl;
	for (int i = 1; i <= n; ++i)
	{
		if (!v[i] || vis[fir[i]]) continue;
		if (dis[i] == dis[t])
            ++cnt, vis[fir[i]] = true;
	}
	// cnt��ʾ���е�t�ľ���Ϊdis[t]�Ľڵ�������
	cout << cnt << endl;
    for (int i = 1; i <= n; i++)
		cout << dis[i] << " ";
    cout << endl;
	for (int i = 1; i <= n; i++)
		cout << fir[i] << " ";
    cout << endl;
	for (int i = 1; i <= n; ++i)
		if (v[i])
		{
			++f[i];
			// ���ڹ������һ����midΪ������
			// fir[i] == fir[s]��ʾi��s��ͬһ�����£��·��Ϊ i ==> t
			// fir[i] == fir[t]��ʾi��t��ͬһ�����£��·��Ϊ i ==> s
			// fir[i] != fir[s] && fir[i] != fir[t]��ʾi��s��t������ͬһ�����£��·��Ϊ i ==> t
			// f[i]��ʾ�Խڵ�iΪ�յ��monastery�ڵ������
			if (fir[i] == fir[s] && cnt < 3) ++f[t];
			else if (fir[i] == fir[t] && cnt < 3) ++f[s];
			else if (fir[i] != fir[s] && fir[i] != fir[t] && cnt < 2) ++f[t];
		}
    for (int i = 1; i <= n; i++)
		cout << dfn[i] << " ";
    cout << endl;
    // dfn[]��ʾdfsʱ�Ľڵ�˳��
    for (int i = 1; i <= n; i++)
		cout << f[i] << " ";
    cout << endl;

	int ans = 0, ans1 = 0;
	if (!v[mid]) ans = m, ans1 = 1;
	for (int i = n; i > 1; --i)
	{
		f[fa[dfn[i]]] += f[dfn[i]];
		if (!v[dfn[i]] && ans < f[dfn[i]]) ans = f[dfn[i]], ans1 = 1;
		else if (!v[dfn[i]] && ans == f[dfn[i]]) ++ans1;
	}
	printf("%d %d\n", ans, ans1);
}

