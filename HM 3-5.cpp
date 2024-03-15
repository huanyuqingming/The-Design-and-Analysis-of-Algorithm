// https://acm.sjtu.edu.cn/OnlineJudge/problem/1431
// reference: https://blog.csdn.net/qq_54847231/article/details/123850995?spm=1001.2014.3001.5506

#include <bits/stdc++.h>
using namespace std;

struct sth
{
    int w = 0;
    int v = 0;
    int c = 0;
};

int n, W;
vector<sth> store;

int main()
{
    cin >> n >> W;
    sth t;
    t.w = t.v = t.c = -1;
    store.push_back(t);
    for (int i = 0; i < n; ++i)
    {
        cin >> t.w >> t.v >> t.c;
        if (t.c <= 10000)
        {
            sth p;
            // p.w = t.w;
            // p.v = t.v;
            // p.c = 1;
            // store.push_back(p);
            int j = 1, c = t.c;
            for (; j <= c; j = j * 2)
            {
                p.w = t.w * j;
                p.v = t.v * j;
                p.c = 1;
                store.push_back(p);
                c -= j;
            }
            p.w = t.w * c;
            p.v = t.v * c;
            p.c = 1;
            store.push_back(p);
        }
        else
            store.push_back(t);
    }
    int l = store.size();
    // for (int i = 0; i < l; ++i)
    //     cout << store[i].w << ' ' << store[i].v << ' ' << store[i].c << endl;
    int dp[W+1] = {};
    for (int i = 1; i < l; ++i)
        if (store[i].c <= 10000)
            for (int j = W; j >= store[i].w; --j)
                dp[j] = max(dp[j], +dp[j - store[i].w] + store[i].v);
        else for (int j = store[i].w; j <= W; ++j)
                dp[j] = max(dp[j], +dp[j - store[i].w] + store[i].v);
    cout << dp[W];
    return 0;
}