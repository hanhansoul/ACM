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

char S[300];
string str;
vector<char> Q;
stack<char> T, R;
stack<int> G;
map<char, int> E;
map<string, char> C;
int N, M, K;
int F[220][220], D[220][220];
void build()
{
	while (!T.empty()) T.pop();
	while (!R.empty()) R.pop();
	for (int i = 0; i < Q.size(); i++)
	{
		char s = Q[i];
		if (s == '(')
		{
			T.push(s);
			continue;
		}
		if (s == ')')
		{
			while (!T.empty() && T.top() != '(')
			{
				R.push(T.top());
				T.pop();
			}
			continue;
		}
		if ('A' <= s && s <= 'Z' || s == '1' || s == '0') R.push(s);
		else
		{
			while (!T.empty())
			{
				char t = T.top();
				if (E[t] >= E[s])
				{
					T.push(s);
					break;
				}
				else
				{
					R.push(t);
					T.pop();
				}
			}
		}

	}
}
int reg[30];
int eval()
{
	T = R;
	char ch;
	while (!G.empty()) G.pop();
	while (!T.empty())
	{
		char t = T.top();
		T.pop();
		if ('A' <= t && t <= 'Z')
			G.push(reg[t - 'A']);
		else if (t == '0' || t == '1')
			G.push(t - '0');
		else
		{
			int x1, x2;
			if (t == '|')
			{
				x1 = G.top();
				G.pop();
				x2 = G.top();
				G.pop();
				G.push(x1 | x2);
			}
			else if (t == '&')
			{
				x1 = G.top();
				G.pop();
				x2 = G.top();
				G.pop();
				G.push(x1 & x2);
			}
			else if (t == '!')
			{
				x1 = G.top();
				G.pop();
				G.push(1 - x1);
			}
		}
	}
	return G.top();
}

int dd[4][2] = {{1, 0}, {0, 1}, { -1, 0}, {0, -1}};
int main()
{
	// freopen("input.txt", "r", stdin);
	str.clear();
	C.clear();
	C.insert(make_pair("OR", '|'));
	C.insert(make_pair("AND", '&'));
	C.insert(make_pair("NOT", '!'));
	C.insert(make_pair("TRUE", '1'));
	C.insert(make_pair("FALSE", '0'));
	char ch, ss[2];
    ss[1] = '\0';
	for (ch = 'A'; ch <= 'Z'; ch++)
    {
        ss[0] = ch;
        C.insert(make_pair(string(ss), ch));
    }

	gets(S);
	strcat(S, " ");
	int len = strlen(S);
	for (int i = 0; i < len; i++)
	{
		if (!str.empty() && (S[i] == '(' || S[i] == ')' || S[i] == ' '))
		{
			Q.push_back(C[str]);
			str.clear();
		}
		if (S[i] == '(' || S[i] == ')')
		{
			Q.push_back(S[i]);
			continue;
		}

		if (S[i] != ' ')
			str += S[i];
	}
	Q.push_back('#');

	E.clear();
	E.insert(make_pair('#', 0));
	E.insert(make_pair('|', 1));
	E.insert(make_pair('&', 2));
	E.insert(make_pair('!', 3));
	E.insert(make_pair('(', 4));
	E.insert(make_pair(')', 4));
	build();

    /*
    while(!R.empty())
    {
        cout << R.top() << " ";
        R.pop();
    }
	cout << endl;
    return 0;
    */
	scanf("%d%d%d", &N, &M, &K);
	int x, y, p;
	memset(F, 0, sizeof(F));
	memset(D, 0, sizeof(D));
	memset(reg, 0, sizeof(reg));
	for (int i = 1; i <= M; i++)
	{
		scanf("%d%d", &x, &y);
		F[x + N][y + N] = 1;
	}
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d%s", &x, &y, ss);
		D[x + N][y + N] |= (1 << (ss[0] - 'A'));
	}
	bool finish = false;
	x = y = N, p = 0;
	printf("0 0\n");
	while (!finish)
	{
		if (F[x][y])
		{
		    int t = eval();
		    //cout << "reg == " << reg[0] << " " << reg[1] << endl;
			if (t) p = (p + 1) % 4;
			else p = (p - 1 + 4) % 4;
			//cout << "000000" << endl;
		}
		if (D[x][y])
		{
		    //cout << "pos == " << x - N << " " << y - N << endl;
		    //cout << D[x][y] << endl;
		    //cout << "reg == " << reg[0] << " " << reg[1] << endl;
			for (int i = 0; i < 26; i++)
				if (D[x][y] & (1 << i))
					reg[i] = 1 - reg[i];
            //cout << "reg == " << reg[0] << " " << reg[1] << endl;
            //cout << "111111" << endl;
		}
		x += dd[p][0], y += dd[p][1];
		if (x < 0 || x > 2 * N || y < 0 || y > 2 * N) finish = true;
		else printf("%d %d\n", x - N, y - N);
	}
	return 0;
}
