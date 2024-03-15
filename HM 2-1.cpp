// https://acm.sjtu.edu.cn/OnlineJudge/problem/1985

#include <bits/stdc++.h>
using namespace std;

/*
    Input
        n: number of vertices
        s, t: the start and end of the path
        edges: directed edges in the graph, first->second
    Return
        Empty vector if no path exists,
        vertices on the path from s to t otherwise.
    Note
        Vertices are numbered from 1 to n.
        You can use global variables, and declare some
        other functions to reduce code difficulty.
*/

int graph[1001][1001] = {};
int marked[1001] = {};

vector<int> find_path(int n, int s, int t, vector<pair<int, int>> &edges)
{
    vector<int> passed;
    stack<int> dfs;
    int u;
    int father[n + 1] = {};
    bool founded = false;
    dfs.push(s);
    while (!dfs.empty())
    {
        u = dfs.top();
        dfs.pop();
        marked[u] = 1;
        if (u == t)
            {
                founded = true;
                break;
            }
        for (int i = 1; i <= n; ++i)
        {
            if (graph[u][i] == 1 && marked[i] == 0)
            {
                dfs.push(i);
                father[i] = u;
            }
        }
    }
    if (founded)
    {
        int i = t;
        while (i != s)
        {
            passed.push_back(i);
            i = father[i];
        }
        passed.push_back(s);
        reverse(passed.begin(), passed.end());
    }
    return passed;
}

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        graph[u][v] = 1;
    }
    auto ret = find_path(n, s, t, edges);
    if (!ret.size())
        cout << "-1\n";
    else
    {
        // check if solution is good
        // when failed, you will see info locally,
        // or "Program killed by signal 6 (Aborted)" on OJ
        /*
        assert (ret.front() == s);
        assert (ret.back() == t);
        assert (set <int> (ret.begin(), ret.end()).size() == ret.size());
        set < pair <int, int> > set_edges(edges.begin(), edges.end());
        for (int i = 1; i < (int) ret.size(); i++) {
            assert ( set_edges.count ({ret[i - 1], ret[i]}) );
        }
        */
        cout << ret.size() << '\n';
        for (auto i : ret)
        {
            cout << i << (i == t ? '\n' : ' ');
        }
    }
}