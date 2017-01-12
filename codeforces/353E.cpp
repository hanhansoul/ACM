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
#define MAXN 1000010

char S[MAXN << 1], ch;
int len, ans, cnt, st, en, ll;
int main()
{
	// freopen("input.txt", "r", stdin);
	scanf("%s", S + 1);
	len = strlen(S + 1), ch = S[len], ll = 0;
	while(S[ll + 1] == ch) ll++;
	memcpy(S + len + 1, S + 1, ll);
    st = ll + 1, en = st + len - 1;
    cnt = ans = 0;
	for(int i = st, k; i < en; i++)
    {
        k = 0;
        while(i < en && S[i] == S[i + 1]) i++, k++;
        if(k) ans++, ans += cnt / 2, cnt = 0;
        else cnt++;
    }
    if(S[en] != S[en - 1]) cnt++;
    ans += cnt / 2;
	printf("%d\n", ans);
	return 0;
}
