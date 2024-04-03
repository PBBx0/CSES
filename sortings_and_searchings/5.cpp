#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> ev;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        ev.emplace_back(a, 1);
        ev.emplace_back(b, -1);
    }
    sort(ev.begin(), ev.end(), [](auto f, auto s) {
        if (f.first != s.first)
            return f.first < s.first;
        return f.second > s.second;
    });
    int cur = 0, res = 0;
    for (auto [_, x] : ev) {
        cur += x;
        res = max(res, cur);
    }
    cout << res << '\n';
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