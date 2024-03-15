// https://acm.sjtu.edu.cn/OnlineJudge/problem/1344

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct node
{
    int no = 0;
    long long weight = INF;
    node *next = NULL;
};

int main()
{
    int n, m;
    cin >> n >> m;
    node *adj[n + 1];
    long long l[n + 1];
    int father[n + 1];
    bool flags[n + 1] = {};
    for (int i = 0; i <= n; ++i)
    {
        adj[i] = NULL;
        l[i] = INF;
        father[i] = 0;
    }
    l[1] = 0; // 1为起点
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        node *p = new node;
        cin >> u >> v >> w;
        p->no = v;
        p->weight = w;
        p->next = adj[u];
        adj[u] = p;
    }
    int isUpdate = 0;
    node *p;
    for (int i = 1; i <= n; ++i)
    {
        isUpdate = 0;
        for (int j = 1; j <= n; ++j)
        {
            p = adj[j];
            while (p != NULL)
            {
                if (l[p->no] > l[j] + p->weight)
                {
                    l[p->no] = l[j] + p->weight;
                    father[p->no] = j;
                    isUpdate = p->no;
                }
                p = p->next;
            }
        }
    }
    if (isUpdate == 0)
    {
        cout << "No";
    }
    else
    {
        cout << "Yes" << endl;
        int i = isUpdate;
        while (!flags[i])
        {
            flags[i] = true;
            i = father[i];
        }
        int cnt = 1;
        int j = father[i];
        vector<int> path;
        while (j != i)
        {
            path.push_back(j);
            j = father[j];
            ++cnt;
        }
        path.push_back(i);
        reverse(path.begin(), path.end());
        cout << cnt << endl;
        for (int i = 0; i < path.size(); ++i)
            cout << path[i] << ' ';
    }
}