// https://acm.sjtu.edu.cn/OnlineJudge/problem/1428

#include <bits/stdc++.h>
using namespace std;

struct node
{
    int no = 0;
    int weight = INT_MAX;
    node *next = NULL;
};

int main()
{
    int n, m, sum = 0;
    cin >> n >> m;
    node *adj[n + 1] = {};
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        node *p = new node, *q = new node;
        cin >> u >> v >> w;
        if (u != v)
        {
            p->no = v;
            p->weight = w;
            p->next = adj[u];
            adj[u] = p;
            q->no = u;
            q->weight = w;
            q->next = adj[v];
            adj[v] = q;
        }
    }
    int MST[n+1] = {};
    bool map[n+1] = {};
    MST[1] = 1;
    map[1] = true;
    int cost[n+1] = {};
    for (int i = 0; i <= n; ++i)
        cost[i] = INT_MAX;
    // cost[1] = 0;
    node *p = adj[1];
    while (p != NULL)
    {
        if (p->weight < cost[p->no])
        {
            cost[p->no] = p->weight;
        }
        p = p->next;
    }
    int next;
    for (int i = 2; i <= n; ++i)
    {
        next = min_element(cost, cost + n + 1) - cost;
        MST[i] = next;
        map[next] = true;
        sum += cost[next];
        cost[next] = INT_MAX;
        p = adj[next];
        while (p != NULL)
        {
            if (p->weight < cost[p->no] && map[p->no] == false)
            {
                cost[p->no] = p->weight;
            }
            p = p->next;
        }
    }
    cout << sum;
    return 0;
}
