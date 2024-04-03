#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> l(n), r(n), c(n);
    vector<ll> dp(n + 1);
    vector<pair<int, int>> ev;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i] >> c[i];
        ev.emplace_back(l[i], i + 1);
        ev.emplace_back(r[i], -i - 1);
    }
    sort(ev.begin(), ev.end(), [&](auto f, auto s) {
        if (f.first != s.first) return f.first < s.first;
        return f.second > s.second;
    });
    ll cur = 0;
    for (auto [_, idx] : ev) {
        if (idx > 0) {
            dp[idx] = cur + c[idx - 1];
        } else {
            cur = max(cur, dp[-idx]);
        }
    }
    cout << cur << '\n';
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