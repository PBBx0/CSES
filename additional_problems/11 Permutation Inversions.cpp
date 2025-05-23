#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
void solve() {
    int n, k;
    cin >> n >> k;
    ll dp[n + 1][k + 1];
    dp[1][0] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i][0] = 1;
        for (int j = 1; j <= min(k, i * (i - 1) / 2); ++j) {
            dp[i][j] = dp[i][j - 1];
            if (j <= (i - 2) * (i - 1) / 2) dp[i][j] += dp[i - 1][j];
            if (j - i >= 0) dp[i][j] -= dp[i - 1][j - i];
            dp[i][j] = (dp[i][j] % MOD + MOD) % MOD;
        }
    }
    cout << dp[n][k] << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    solve();
    return 0;
}