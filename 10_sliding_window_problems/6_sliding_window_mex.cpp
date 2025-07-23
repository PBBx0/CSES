#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& el : a) {
        cin >> el;
        if (el > n) el = n;
    }
    vector<int> cnt(n + 1);
    for (int i = 0; i < k; ++i) ++cnt[a[i]];
    set<pair<int, int>> s;
    for (int i = 0; i <= n; ++i) {
        s.emplace(cnt[i], i);
    }
    cout << s.begin()->second << ' ';
    for (int i = 0; i < n - k; ++i) {
        s.erase({cnt[a[i]], a[i]});
        --cnt[a[i]];
        s.emplace(cnt[a[i]], a[i]);
        s.erase({cnt[a[i + k]], a[i + k]});
        ++cnt[a[i + k]];
        s.emplace(cnt[a[i + k]], a[i + k]);
        cout << s.begin()->second << ' ';
    }
    cout << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
