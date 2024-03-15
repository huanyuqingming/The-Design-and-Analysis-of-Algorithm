// https://acm.sjtu.edu.cn/OnlineJudge/problem/1301

#include <bits/stdc++.h>
using namespace std;

struct node
{
    int x;
    int *p;
};

vector<node> a;
int n;

void counting_inversions(int l, int r)
{
    int m = (l + r) / 2;
    if (r - l <= 1)
    {
        if (a[l].x > a[r].x)
        {
            swap(a[l], a[r]);
            ++*a[l].p;
            ++*a[r].p;
        }
    }
    else
    {
        counting_inversions(l, m);
        counting_inversions(m + 1, r);
        int i = 0, j = 0, k = l;
        vector<node> b, d;
        b.resize(m - l + 1);
        d.resize(r - m);
        for (int _ = 0; _ <= m - l; ++_)
            b[_] = a[l + _];
        for (int _ = 0; _ <= r - m - 1; ++_)
            d[_] = a[m + 1 + _];
        while (i <= m - l && j <= r - m - 1)
        {
            if (b[i].x > d[j].x)
            {
                a[k] = d[j];
                *d[j].p += m - l - i + 1;
                for (int _ = i; _ <= m - l; ++_)
                    ++*b[_].p;
                ++j;
                ++k;
            }
            else
            {
                a[k] = b[i];
                ++i;
                ++k;
            }
        }
        if (i <= m - l)
            for (; k <= r; ++k, ++i)
                a[k] = b[i];
        if (j <= r - m - 1)
            for (; k <= r; ++k, ++j)
                a[k] = d[j];
    }
}

int main()
{
    cin >> n;
    int cnt[n] = {};
    a.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].x;
        a[i].p = &cnt[i];
    }
    counting_inversions(0, n - 1);
    for (int i = 0; i < n; i++)
        cout << *a[i].p << ' ';
}