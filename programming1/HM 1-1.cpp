// https://acm.sjtu.edu.cn/OnlineJudge/problem/1953

#include <bits/stdc++.h>
using namespace std;

pair<int, int> partition(vector<int> &a, int pivot)
{
    int l = 0, r = a.size() - 1, e = 0;
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

int main()
{
    int n, pivot;
    cin >> n >> pivot;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    auto result = partition(arr, pivot);
    int l = result.first;
    int r = result.second;
    for (auto i : arr)
        cout << i << ' ';
    cout << '\n' << l << ' ' << r << '\n';
}
