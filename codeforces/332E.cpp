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
#define MAXN 2010
#define MAXM 1000010

string P, S, E[MAXN], R[MAXN];
int K, ls, lp;
int Sa[MAXN], Sb[MAXM];
int F[MAXN], TF[MAXN];
bool hasAns;
// trie
struct TRIE
{
	int next[100], mark;
} T[MAXN];
int tot;
void build(string str, int num)
{
	int rt = 0;
	for (int i = 0; i < str.length(); i++)
	{
		int mm = str[i] - 32;
		if (T[rt].next[mm] == -1)
        {
            T[rt].next[mm] = ++tot;
            memset(T[tot].next, -1, sizeof(T[tot].next));
            T[tot].mark = -1;
        }
		rt = T[rt].next[mm];
	}
	if (T[rt].mark != -1) Sa[num + 1] = T[rt].mark;
	else T[rt].mark = num, Sa[num + 1] = num;
}
int match(string str)
{
	int rt = 0;
	for (int i = 0; i < str.length(); i++)
	{
		int mm = str[i] - 32;
		if (T[rt].next[mm] == -1) return -1;
		rt = T[rt].next[mm];
	}
	return T[rt].mark;
}
void solve(int nn)
{
    // cout << nn << endl;
	for (int i = 0; i < nn; i++)
	{
		R[i].clear();
		for (int j = i; j < ls; j += nn)
			R[i] += S[j];
	}
	tot = 0;
	memset(T[0].next, -1, sizeof(T[0].next));
	T[0].mark = -1;
	for (int i = 0; i < nn; i++)
		build(R[i], i);
	for (int i = 0; i < K; i++)
		Sb[i + 1] = match(E[i]);
    //
    /*
	cout << nn << " " << K << endl;
	for (int i = 1; i <= nn; i++)
		cout << Sa[i] << " ";
	cout << endl;
	for (int i = 1; i <= K; i++)
		cout << Sb[i] << " ";
	cout << endl;
    */
	//
    bool ha = true;
	for (int i = nn, k = K; k >= 1 && i >= 1; i--, k--)
	{
		for (; k >= 1; k--)
			if (Sa[i] == Sb[k])
			{
				TF[k] = 1;
				break;
			}else TF[k] = 0;
		if (k == 0) ha = false;
	}

	if (ha)
	{
		hasAns = true;
		int res = 0;
		for (int i = 1; res == 0 && i <= K; i++)
		{
			if (TF[i] < F[i]) res = 1;
			else if (TF[i] > F[i]) res = -1;
		}
		if (res == 1) memcpy(F + 1, TF + 1, K * sizeof(int));
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	char ch;
	while ((ch = getchar()) != '\n') P += ch;
	while ((ch = getchar()) != '\n') S += ch;
	cin >> K;
	lp = P.length(), ls = S.length();
	// cout << P << endl << S << endl << K << endl;
	// cout << lp << " " << ls << endl;
	int pn = 0, nn, mm;
	for (int i = 0; i < K; i++)
	{
		E[i].clear();
		for (int j = i; j < lp; j += K)
			E[i] += P[j];
		pn = max(pn, (int)E[i].length());
	}
	// solve
	// nn表示S每一行的字符数
	// pn表示S的行数
	// mm表示最末行剩余的字符数
	hasAns = false;
	for (int i = 1; i <= K; i++) F[i] = 1;
	if (lp % K == 0)
	{
		if (ls % pn == 0)
		{
			nn = ls / pn;
			solve(nn);
		}
	}
	else if (lp % K != 0)
	{
	    pn--;
	    if(pn)
        {
            nn = ls / pn, mm = ls % pn;
            for(;mm <= nn;)
            {
                solve(nn);
                mm += pn, nn--;
            }
        }else solve(ls);
	}
	if (hasAns)
	{
		for (int i = 1; i <= K; i++)
			printf("%d", F[i]);
		printf("\n");
	}
	else printf("0\n");
	return 0;
}
