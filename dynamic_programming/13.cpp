#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll& el : a) cin >> el;
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    for (int i = 0; i <= n; ++i) dp[i][i] = 0;
    for (int i = 0; i < n; ++i) dp[i][i + 1] = a[i];
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            dp[i][i + len] = max(min(dp[i + 1][i + len - 1], dp[i][i + len - 2]) + a[i + len - 1],
                                 min(dp[i + 2][i + len], dp[i + 1][i + len - 1]) + a[i]);
        }
    }
    cout << dp[0][n] << '\n';
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