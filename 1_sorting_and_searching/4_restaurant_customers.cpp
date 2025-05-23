#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> ev;
    ev.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        ev.emplace_back(l, 1);
        ev.emplace_back(r, -1);
    }
    sort(all(ev));
    int cur = 0;
    int ans = 0;
    for (auto [_, d] : ev) {
        cur += d;
        ans = max(ans, cur);
    }
    cout << ans << '\n';
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