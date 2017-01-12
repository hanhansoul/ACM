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
/*
    treap
*/
int N, M;
vector<int> P, E;

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	int k;
	for(int i=1;i<=M;i++)
    {
        scanf("%d", &k);
        P.push_back(k);
    }
    int pos = 0;
    while(N--)
    {
        scanf("%d", &k);
        if(k==-1)
        {

        }else
        {
            pos++;
            E.push_back(k);
            Insert();
        }
    }
	return 0;
}


