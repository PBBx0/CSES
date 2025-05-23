#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
using ld = long double;
void solve() {
    int lo, hi, n;
    cin >> n >> lo >> hi;
    const int T = 601;
    vector<array<ld, T>> dp(n + 1);
    dp[0][0] = 1e8;
    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < T; ++x) {
            for (int d = 1; d <= 6 && x + d < T; ++d) {
                dp[i + 1][x + d] += dp[i][x] / 6;
            }
        }
    }
    ld res = 0;
    for (int t = lo; t <= hi; ++t) {
        res += dp[n][t];
    }
    cout << fixed << setprecision(6);
    cout << res / 1e8 << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}