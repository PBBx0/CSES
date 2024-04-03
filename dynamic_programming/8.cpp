#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int MOD = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int& el : a) {cin >> el; --el;}
    vector<vector<ll>> dp(n + 1, vector<ll>(m));
    bool first = true;
    for (int i = 0; i < n; ++i) {
        if (first) {
            if (a[i] == -1) {
                for (int d = 0; d < m; ++d) {
                    dp[i][d] = 1;
                }
            } else {
                dp[i][a[i]] = 1;
            }
            first = false;
            continue;
        }
        if (a[i] == -1) {
            for (int d = 0; d < m; ++d) {
                for (int d2 = max(0, d - 1); d2 < min(m, d + 2); ++d2) {
                    dp[i][d] += dp[i - 1][d2];
                }
                dp[i][d] %= MOD;
            }
        } else {
            for (int d = max(0, a[i] - 1); d < min(m, a[i] + 2); ++d) {
                dp[i][a[i]] += dp[i - 1][d];
            }
            dp[i][a[i]] %= MOD;
        }
    }
    cout << accumulate(dp[n - 1].begin(), dp[n - 1].end(), 0LL) % MOD << '\n';
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