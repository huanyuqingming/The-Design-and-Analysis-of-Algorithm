// https://acm.sjtu.edu.cn/OnlineJudge/problem/1899

#include <bits/stdc++.h>
using namespace std;

struct node
{
    int no = 0;
    node *next = NULL;
};

int Gf[1002][1002] = {};

int main()
{
    int n, m;
    cin >> n >> m;
    node *adj[n + 2] = {};
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v;
        node *p = new node;
        p->no = v;
        p->next = adj[u];
        adj[u] = p;
        node *q = new node;
        q->no = u;
        q->next = adj[v];
        adj[v] = q;
    }
    bool map[n + 2] = {};
    int c[n + 1] = {};
    vector<int> red, blue;
    for (int i = 1; i <= n; ++i)
    {
        if (map[i] == false)
        {
            queue<int> bfs;
            bfs.push(i);
            map[i] = true;
            red.push_back(i);
            c[i] = 1;
            int color = 1;
            while (!bfs.empty())
            {
                int u = bfs.front();
                bfs.pop();
                node *p = adj[u];
                while (p != NULL)
                {
                    if (map[p->no] == false)
                    {
                        if (c[u] == 2)
                        {
                            red.push_back(p->no);
                            c[p->no] = 1;
                        }
                        else
                        {
                            blue.push_back(p->no);
                            c[p->no] = 2;
                        }
                        map[p->no] = true;
                        bfs.push(p->no);
                    }
                    p = p->next;
                }
            }
        }
    }

    // int r = red.size(), b = blue.size();
    // cout << endl
    //      << "r = " << r << endl
    //      << "r has ";
    // sort(red.begin(), red.end());
    // for (int i = 0; i < r; ++i)
    //     cout << red[i] << ' ';
    // cout << endl
    //      << "b = " << b << endl
    //      << "b has ";
    // sort(blue.begin(), blue.end());
    // for (int i = 0; i < b; ++i)
    //     cout << blue[i] << ' ';

    for (int i = 0; i < red.size(); ++i)
    {
        node *p = adj[red[i]];
        while (p != NULL)
        {
            Gf[red[i]][p->no] = INT_MAX;
            p = p->next;
        }
    }

    for (int i = 0; i < red.size(); ++i)
    {
        node *p = new node;
        p->no = red[i];
        p->next = adj[0];
        adj[0] = p;
        node *q = new node;
        q->no = 0;
        q->next = adj[red[i]];
        adj[red[i]] = q;
        Gf[0][red[i]] = 1;
    }
    for (int i = 0; i < blue.size(); ++i)
    {
        node *p = new node;
        p->no = blue[i];
        p->next = adj[n + 1];
        adj[n + 1] = p;
        node *q = new node;
        q->no = n + 1;
        q->next = adj[blue[i]];
        adj[blue[i]] = q;
        Gf[blue[i]][n + 1] = 1;
    }

    // for (int i = 0; i <= n + 1; ++i)
    // {
    //     for (int j = 0; j <= n + 1; ++j)
    //     {
    //         cout << Gf[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    bool isConnected = true;
    vector<int> iset;
    while (isConnected)
    {
        isConnected = false;
        queue<int> bfs;
        bool map[n + 2] = {};
        int father[n + 2] = {};
        bfs.push(0);
        map[0] = true;
        while (!bfs.empty())
        {
            int u = bfs.front();
            bfs.pop();
            if (u == n + 1)
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
            for (int i = 1; i <= n; ++i)
            {
                if (map[i])
                {
                    for (int j = 0; j <= red.size(); ++j)
                    {
                        if (red[j] == i)
                        {
                            iset.push_back(i);
                        }
                    }
                }
                else
                {
                    for (int j = 0; j <= blue.size(); ++j)
                    {
                        if (blue[j] == i)
                        {
                            iset.push_back(i);
                        }
                    }
                }
            }
            break;
        }

        int tmp = n + 1;
        int min = INT_MAX;
        if (father[n + 1] != 0)
        {
            while (tmp != 0)
            {
                if (Gf[father[tmp]][tmp] < min)
                {
                    min = Gf[father[tmp]][tmp];
                }
                tmp = father[tmp];
            }
            tmp = n + 1;
            while (tmp != 0)
            {
                Gf[father[tmp]][tmp] -= min;
                Gf[tmp][father[tmp]] += min;
                tmp = father[tmp];
            }
        }
    }

    cout << iset.size() << endl;
    for (int i = 0; i < iset.size(); ++i)
    {
        cout << iset[i] << ' ';
    }

    return 0;
}
