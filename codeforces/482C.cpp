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
double F[MAXN][25];     // R[msk][i]��¼msk�µĵ�i�������ֵ
int R[MAXN][25];        // R[msk][i]��¼msk�µĵ�i��������ַ�����Ϊһ��bit mask��
int C[MAXN][25];        // R[msk][i]��¼msk�µĵ�i��������ַ���������
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for(int i=1;i<=N;i++)
        cin >> S[i];
    len = S[1].length();

	return 0;
}
