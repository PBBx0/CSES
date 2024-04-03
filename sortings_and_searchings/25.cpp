#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    unordered_map<int, vector<pair<int, int>>> mp;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            mp[a[i] + a[j]].emplace_back(i, j);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int cur = x - a[i] - a[j];
            if (!mp.contains(cur)) continue;
            for (auto [f, s] : mp[cur]) {
                if (f != i && s != i && f != j && s != j) {
                    cout << i + 1 << ' ' << j + 1 << ' ' << f + 1 << ' ' << s + 1 << '\n';
                    return;
                }
            }
        }
    }
    cout << "IMPOSSIBLE" << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}