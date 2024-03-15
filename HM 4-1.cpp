// https://acm.sjtu.edu.cn/OnlineJudge/problem/1449

#include <bits/stdc++.h>
using namespace std;

struct node
{
    int no = 0;
    node *next = NULL;
};

int n, m;

int main()
{
    cin >> n >> m;
    node *adj[n + 1] = {};
    int Gf[201][201] = {};
    int u, v, c, f = 0;
    bool isConnected = true;

    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v >> c;
        if (u != v)
        {
            if (Gf[u][v] == 0 && Gf[v][u] == 0)
            {
                node *p = new node;
                p->no = v;
                p->next = adj[u];
                adj[u] = p;
                node *q = new node;
                q->no = u;
                q->next = adj[v];
                adj[v] = q;
            }
            Gf[u][v] += c;
        }
    }

    while (isConnected)
    {
        queue<int> bfs;
        bool map[n + 1] = {};
        int father[n + 1] = {};
        bfs.push(1);
        map[1] = true;
        while (!bfs.empty())
        {
            isConnected = false;
            int u = bfs.front();
            bfs.pop();
            if (u == n)
            {
                isConnected = true;
                break;
            }
            node *p = adj[u];
            while (p != NULL)
            {
                if (map[p->no] == false && Gf[u][p->no] != 0)
                {
                    map[p->no] = true;
                    father[p->no] = u;
                    bfs.push(p->no);
                }
                p = p->next;
            }
        }

        if (!isConnected)
        {
            break;
        }

        int tmp = n;
        int min = INT_MAX;
        if (father[n] != 0)
        {
            while (tmp != 1)
            {
                if (Gf[father[tmp]][tmp] < min)
                {
                    min = Gf[father[tmp]][tmp];
                }
                tmp = father[tmp];
            }
            f += min;
            tmp = n;
            while (tmp != 1)
            {
                Gf[father[tmp]][tmp] -= min;
                Gf[tmp][father[tmp]] += min;
                tmp = father[tmp];
            }
        }
    }

    cout << f;
    return 0;
}