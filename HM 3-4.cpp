// https://acm.sjtu.edu.cn/OnlineJudge/problem/1856

#include <bits/stdc++.h>
using namespace std;

int n;
int w[21][21] = {};
int sp[21][21] = {};
int memo[1 << 21][21] = {};

void Dij(int n, int s)
{
    int tdist[n + 1];
    int marked[n + 1] = {};
    int cnt = 1;
    for (int i = 1; i <= n; ++i)
        tdist[i] = INT_MAX;
    tdist[s] = 0;
    marked[s] = 1;

    while (cnt < n)
    {
        int v = 0;
        int d = INT_MAX;
        for (int i = 1; i <= n; ++i)
        {
            if (marked[i] == 0)
            {
                for (int j = 1; j <= n; ++j)
                {
                    if (marked[j] == 1 && (tdist[j] + w[j][i] < d))
                    {
                        d = tdist[j] + w[j][i];
                        v = i;
                    }
                }
            }
        }
        marked[v] = 1;
        tdist[v] = d;
        ++cnt;
    }
    for (int i = 1; i <= n; ++i)
        sp[s][i] = tdist[i];
}

int TSP(int i, int state)
{
    int min = INT_MAX, tmp = 0;
    if (state == (1 << n) - 1)
    {
        return sp[i][1];
    }
    if (memo[state][i] != 0)
    {
        return memo[state][i];
    }
    for (int j = 1; j <= n; ++j)
    {
        if (!(state & (1 << (j - 1))))
        {
            int state1 = state | (1 << (j - 1));
            
            tmp = sp[i][j] + TSP(j, state1);
            if (tmp < min)
                min = tmp;
        }
    }
    memo[state][i] = min;
    return min;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> w[i][j];
    for (int i = 1; i <= n; ++i)
        Dij(n, i);
    cout << TSP(1, 1);
}