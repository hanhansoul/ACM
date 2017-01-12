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
#define MAXN 200010

int N, M, P;
int Sa[MAXN], Sb[MAXN];
vector<int> R;
map<int, int> Ca, Cb;
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &N, &M, &P);
	for (int i = 1; i <= N; i++)
		scanf("%d", &Sa[i]);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d", &Sb[i]);
		Cb[Sb[i]]++;
	}
	for (int i = 1; i <= P && i <= N; i++)
	{
		Ca.clear();
		int cnt = 0;
		for (int j = i, k = 1; j <= N; j += P, k++)
		{
			Ca[Sa[j]]++;
			if (Ca[Sa[j]] <= Cb[Sa[j]]) cnt++;
			if (k >= M)
			{
				int pp = j - (M - 1) * P;
				if (cnt == M)
					R.push_back(pp);
				Ca[Sa[pp]]--;
				if (Ca[Sa[pp]] < Cb[Sa[pp]]) cnt--;
			}
		}
	}
	printf("%d\n", R.size());
	sort(R.begin(), R.end());
	for (int i = 0; i < R.size(); i++)
		printf("%d ", R[i]);
	cout << endl;
	return 0;
}
