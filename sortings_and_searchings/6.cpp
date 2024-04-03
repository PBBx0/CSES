#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> dp(n + 1);
    int ma = 0;
    vector<pair<int, int>> ev;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        ev.emplace_back(a, i);
        ev.emplace_back(b, -i);
    }
    sort(ev.begin(), ev.end(), [](auto f, auto s) {
        if (f.first != s.first)
            return f.first < s.first;
        return f.second < s.second;
    });
    for (auto [x, id] : ev) {
        if (id > 0) {
            dp[id] = ma + 1;
        } else {
            ma = max(ma, dp[-id]);
        }
    }
    cout << ma << '\n';
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