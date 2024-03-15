// https://acm.sjtu.edu.cn/OnlineJudge/problem/1299

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct point
{
    long long x, y;
    point(long long _x, long long _y) : x(_x), y(_y) {}
    long long distance_2(const point &other) const
    {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }
};

long long solve(const vector<point> &a, long long l, long long r)
{
    if (l + 1 >= r)
        return INF;
    long long m = (l + r) / 2;
    long long ret = min(solve(a, l, m), solve(a, m, r));
    vector<point> strip;
    for (long long i = l; i < r; ++i)
        if ((a[i].x - a[m].x) * (a[i].x - a[m].x) < ret)
            strip.push_back(a[i]);
    sort(strip.begin(), strip.end(), [](const point &p1, const point &p2)
         { return p1.y < p2.y; });
    for (long long i = 0; i < strip.size(); ++i)
        for (long long j = i + 1; j < strip.size(); ++j)
        {
            if ((strip[i].y - strip[j].y) * (strip[i].y - strip[j].y) >= ret)
                break;
            ret = min(ret, strip[i].distance_2(strip[j]));
        }
    return ret;
}

int main()
{
    long long n;
    cin >> n;
    vector<point> a;
    for (long long i = 0; i < n; ++i)
    {
        long long x, y;
        cin >> x >> y;
        a.push_back(point(x, y));
    }
    sort(a.begin(), a.end(), [](auto &u, auto &v)
         { return u.x < v.x; });
    cout << solve(a, 0, n) << endl;
}
