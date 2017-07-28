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
#define MAXN (1 << 20) + 10
#define LL long long

int N;
string S[55];
LL R[MAXN];
double D[MAXN];
int len;

int popcount(int s)
{
    int c = 0;
    while(s)
    {
        if(s & 1) c++;
        s >>= 1;
    }
    return c;
}

int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		cin >> S[i];
	if (N == 1)
	{
		printf("%.10lf\n", 0.0);
		return 0;
	}
	len = S[0].length();
	int mx = (1 << len) - 1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (i == j) continue;
			int msk = 0;
			for (int k = 0; k < len; k++)
				if (S[i][k] == S[j][k])
					msk |= (1 << k);
			R[msk] |= (1LL << j);
		}
	for (int i = mx; i >= 0; i--)
		for (int j = 0; j < len; j++)
			if (i & (1 << j))
				R[i ^ (1 << j)] |= R[i];
	R[0] = (1LL << N) - 1;

	D[0] = 1.0;
	for (int i = 0; i <= mx; i++)
		for (int j = 0; j < len ; j++)
			if ((i & (1 << j)) && R[i ^ (1 << j)] > 0)
				D[i] += D[i ^ (1 << j)] * (1.0 / (len - __builtin_popcount(i) + 1));

	double ans = 0.0;
	for (int i = 0; i <= mx; i++)
		for (int j = 0; j < N; j++)
			if (R[i] & (1LL << j))
				ans += D[i];

    /*
    int s = 1048575;
    cout << __builtin_popcount(s) << endl;
    cout << popcount(s) << endl;
    int c = 0;
    while(s)
    {
        if(s & 1) c++;
        s >>= 1;
    }
    cout << c << endl;
    */
	printf("%.10lf\n", 1.0 * ans / N);
	return 0;
}
