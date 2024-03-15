// https://acm.sjtu.edu.cn/OnlineJudge/problem/1342

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct node
{
    int no = 0;
    long long weight = INF;
    node* next = NULL;
};

long long w[2501][2501];

long long SP(int n, int s, int t, node* adj[])
{
    long long tdist[n+1];
    int marked[n+1] = {};
    int cnt = 1;
    for (int i = 1; i <= n; ++i)
        tdist[i] = INF;
    tdist[s] = 0;
    marked[s] = 1;

    while (cnt < n)
    {
        int v = 0;
        long long d = INF;
        for (int i = 1; i <= n; ++i)
        {
            if (marked[i] == 0) //i是不在树中的点
            {
                node* q = adj[i];
                while (q != NULL)
                {
                    if (marked[q->no] == 1 && (tdist[q->no] + w[q->no][i] < d))
                    {
                        d = tdist[q->no] + w[q->no][i];
                        v = i;
                    }
                    q = q->next;
                }
            }
        }
        marked[v] = 1;
        tdist[v] = d;
        ++cnt;
    }

    return tdist[t];
}

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    for (int i = 0; i < 2501; ++i)
        for (int j = 0; j < 2501; ++j)
            w[i][j] = INF;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        long long weight;
        cin >> u >> v >> weight;
        if (weight < w[u][v])
            w[u][v] = w[v][u] = weight;
    }

    // for (int i = 1; i <= n; ++i)
    //     w[i][i] = 0;

    node* adj[n+1];
    for (int i = 0; i <= n; ++i)
    {
        adj[i] = NULL;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            if (w[i][j] < INF)
            {
                node* p = new node;
                p->no = j;
                p->weight = w[i][j];
                p->next = adj[i];
                adj[i] = p;
            }
        }
    cout << SP(n, s, t, adj);
}