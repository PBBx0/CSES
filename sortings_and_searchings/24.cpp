#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    auto start = clock();
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < n; ++i) {
        mp[a[i]].emplace_back(i);
    }
    for (int i = 0; i < n; ++i) {
        if ((clock() - start) * 1000 / CLOCKS_PER_SEC > 757) break;
        for (int j = i + 1; j < n; ++j) {
            int cur = x - a[i] - a[j];
            if (!mp.contains(cur)) continue;
            int k = -1;
            for (auto el : mp[cur]) {
                if (el != i && el != j) {
                    k = el;
                    break;
                }
            }
            if (k != -1) {
                cout << i + 1 << ' ' << j + 1 << ' ' << k + 1 << '\n';
                return;
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