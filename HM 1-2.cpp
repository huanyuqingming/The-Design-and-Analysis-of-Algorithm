// https://acm.sjtu.edu.cn/OnlineJudge/problem/1300

#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;

// use precise time as random seed
const int RANDOM_SEED = chrono::system_clock::now().time_since_epoch().count();
mt19937 rng(RANDOM_SEED); // random number generator

int randint(int l, int r) { // rand in [l, r]
    return int(rng() % (r - l + 1) + l);
}

int n, k;
vector<int> a;
void read_input_data_vector()
{
    int m;
    cin >> n >> k >> m;
    a.resize(n);
    for (int i = 0; i < m; i++)
    {
        cin >> a[i];
    }
    unsigned int z = a[m - 1];
    for (int i = m; i < n; i++)
    {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
}

pair<int, int> partition(vector<int> &a, int pivot, int l, int r)
{
    int e = 0;
    while (l + e <= r)
    {
        if (a[l + e] > pivot)
        {
            swap(a[l + e], a[r]);
            --r;
        }
        if (a[l + e] < pivot)
        {
            a[l] = a[l + e];
            ++l;
        }
        if (a[l + e] == pivot)
            ++e;
    }
    for (int i = l; i <= r; ++i)
        a[i] = pivot;
    return {l, r + 1};
}

void find_kth(int l, int r)
{
    auto result = partition(a, a[randint(l, r)], l, r);
    if (k-1 < result.first)
        find_kth(l, result.first-1);
    else if (k-1 >= result.second)
        find_kth(result.second, r);
    else cout << a[k-1];
}

int main()
{
    read_input_data_vector();
    find_kth(0, n-1);
}