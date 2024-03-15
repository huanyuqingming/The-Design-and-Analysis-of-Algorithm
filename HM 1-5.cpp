// https://acm.sjtu.edu.cn/OnlineJudge/problem/1982

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct point
{
    long long x, y;
    point(long long _x, long long _y) : x(_x), y(_y) {}
    double circumference(const point &other1, const point &other2) const
    {
        return sqrt(((x - other1.x) * (x - other1.x) + (y - other1.y) * (y - other1.y)) / 1.0) + sqrt(((x - other2.x) * (x - other2.x) + (y - other2.y) * (y - other2.y)) / 1.0) + sqrt(((other2.x - other1.x) * (other2.x - other1.x) + (other2.y - other1.y) * (other2.y - other1.y)) / 1.0);
    }
};

double solve(const vector<point> &a, long long l, long long r)
{
    if (l + 2 >= r)
        return INF;
    long long m = (l + r) / 2;
    double c = min(solve(a, l, m), solve(a, m, r));
    vector<point> strip;
    for (long long i = l; i < r; ++i)
        if ((abs(a[i].x - a[m].x)) < c / 2)
            strip.push_back(a[i]);
    sort(strip.begin(), strip.end(), [](const point &p1, const point &p2)
         { return p1.y < p2.y; });
    for (long long i = 0; i < strip.size(); ++i)
    {
        for (long long j = i + 1; j < strip.size(); ++j)
        {
            if (abs(strip[i].y - strip[j].y) >= c / 2)
                break;
            for (long long k = j + 1; k < strip.size(); ++k)
            {
                if (abs(strip[i].y - strip[k].y) >= c / 2)
                    break;
                c = min(c, strip[i].circumference(strip[j], strip[k]));
            }
        }
    }
    return c;
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
    cout<<fixed<<setprecision(9);
    cout << solve(a, 0, n) << endl;
}