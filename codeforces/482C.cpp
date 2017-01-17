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
#define MAXN (1 << 20)

int N;
string S[55];
//double F[MAXN][55];     // F[msk][i]记录msk下的第i组的期望值。
//int R[MAXN][55];        // R[msk][i]记录msk下的第i组包含的字符串，为一个bit mask。
//int C[MAXN][55];        // C[msk][i]记录msk下的第i组包含的字符串的数量。

vector<char> E;
map<int, double> F[MAXN];
map<int, double>::iterator it;

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		cin >> S[i];
	len = S[0].length();
	memset(D, 0, sizeof(D));
	for (char ch = 'a'; ch <= 'z'; ch++) E.push_back(ch);
	for (char ch = 'A'; ch <= 'Z'; ch++) E.push_back(ch);
	F[0][1] = 0, R[0][1] = (1 << (N - 1)), C[0][1] = N;

	for (int msk = 0; msk < (1 << (N - 1)); msk++)
		for (it = F[msk].begin(); it != F[msk].end(); it++)
			for (int p = 0; p < len; p++)
			{
				int v = (1 << p);
				int key = it->first;
				double val = it->second;
				if (key & v) continue;
				int nn = msk, mm = 0;
				for (int k = 0; k < E.size(); k++)
				{
				    int cnt = 0;
					for (int i = 0; i < N; i++)
						if (!(msk & (1 << i)) && S[i][p] == E[k])
						{
							nn |= (1 << i);
							cnt++;
						}
                    // (key | v)次数
                    if(cnt) F[nn][key | v] = val ;
				}
			}

	return 0;
}
