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

vector<int> P;
bool B[10000010];
void getPrime(int S)
{
	for (int i = 2; i <= S; i++)
		B[i] = true;
	for (int i = 2; i <= sqrt(S); i++)
		if (B[i])
		{
			for (int j = i; j * i <= S; j++)
				B[j * i] = false;
		}
	for (int i = 0; i <= S; i++)
		if (B[i])
			P.push_back(i);
}
int N, M;
int S[10000010], E[1000010], D[10000010];

int main()
{
	// freopen("input.txt", "r", stdin);
	getPrime(10000000);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &E[i]);

	memset(S, 0, sizeof(S));
	memset(D, 0, sizeof(D));
	int mx = 0;
	for (int i = 0; i < N; i++)
	{
		S[E[i]]++;
		mx = max(mx, E[i]);
	}

	for (int i = 0; i < P.size(); i++)
	{
		int u = P[i];
		if(i >= 1) D[u] = D[P[i - 1]];
		for (int j = 1; u * j <= mx; j++)
			D[u] += S[u * j];
	}

	scanf("%d", &M);
	int l, r, ll, rr, pos;
	vector<int>::iterator it;
	for (int i = 0; i < M; i++)
	{
		scanf("%d%d", &l, &r);
		r = min(r, mx);
		if (r < l)
		{
			printf("0\n");
			continue;
		}
		it = lower_bound(P.begin(), P.end(), l);
		if (it != P.end())
		{
			pos = it - P.begin();
			if (pos == 0) ll = 0;
			else ll = P[pos - 1];
		}
		else
		{
			printf("0\n");
			continue;
		}

		it = lower_bound(P.begin(), P.end(), r);
		if (it != P.end())
		{
			pos = it - P.begin();
			if (P[pos] == r) rr = r;
			else if (pos - 1 >= 0) rr = P[pos - 1];
			else rr = 0;
		}
		else
		{
			rr = P[P.size() - 1];
		}
		// cout << D[rr] << " " << D[ll] << endl;
		printf("%d\n", D[rr] - D[ll]);
	}

	return 0;
}
