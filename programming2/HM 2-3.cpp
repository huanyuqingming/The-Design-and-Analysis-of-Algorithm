// https://acm.sjtu.edu.cn/OnlineJudge/problem/1340

#include <bits/stdc++.h>
using namespace std;

int t;
int cnt;
struct node
{
    int no = 0;
    node *next = NULL;
};

void rdfs(int u, int n, node *radj[], int finish_time[], bool rmap[])
{
    ++t;
    rmap[u] = true;
    node *p = radj[u];
    while (p != NULL)
    {
        if (rmap[p->no] == false)
            rdfs(p->no, n, radj, finish_time, rmap);
        p = p->next;
    }
    finish_time[u] = t;
    ++t;
}

long long SCC(int n, int s, node *adj[], bool map[], int finish_time[])
{
    long long v = 0;
    int u;
    stack<int> dfs;
    node *p;
    dfs.push(s);
    while (!dfs.empty())
    {
        u = dfs.top();
        dfs.pop();
        ++v;
        --cnt;
        p = adj[u];
        finish_time[u] = 0;
        map[u] = true;
        while (p != NULL)
        {
            if (map[p->no] == false)
            {
                dfs.push(p->no);
                map[p->no] = true;
            }
            p = p->next;
        }
    }
    return ((v * (v - 1)) / 2);
}

int main()
{
    int n, m, s;
    cin >> n >> m;
    long long num = 0;
    int finish_time[n + 1] = {};
    bool map[n + 1] = {};
    bool rmap[n + 1] = {};
    node *adj[n + 1];
    node *radj[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        adj[i] = NULL;
        radj[i] = NULL;
    }
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        if (u != v)
        {
            node *p = new node;
            node *q = new node;
            p->no = v;
            q->no = u;
            p->next = adj[u];
            q->next = radj[v];
            adj[u] = p;
            radj[v] = q;
        }
    }

    t = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (rmap[i] == true)
            continue;
        rdfs(i, n, radj, finish_time, rmap);
    }

    cnt = n;
    while (cnt != 0)
    {
        s = max_element(finish_time, finish_time + n + 1) - finish_time;
        num += SCC(n, s, adj, map, finish_time);
    }
    cout << num;
}
