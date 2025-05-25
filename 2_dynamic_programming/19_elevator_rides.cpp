#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<pair<int, int>> dp(1 << n);
    dp[0] = {0, w};
    for (int mask = 1; mask < (1 << n); ++mask) {
        pair<int, int> opt{n, w};
        for (int i = 0; i < n; ++i) if (mask & (1 << i)) {
            int pmask = mask ^ (1 << i);
            auto [x, y] = dp[pmask];
            if (y + a[i] <= w) {
                opt = min(opt, make_pair(x, y + a[i]));
            } else {
                opt = min(opt, make_pair(x + 1, a[i]));
            }
        }
        dp[mask] = opt;
    }
    cout << dp[(1 << n) - 1].first << '\n';
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