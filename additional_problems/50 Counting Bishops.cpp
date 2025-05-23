#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
const int N = 510;
ll dp[N + N], dp2[N + N], dp3[N + N];
void solve() {
    int n, k;
    cin >> n >> k;
    if (k > 2 * n - 1) {
        cout << 0 << '\n';
        return;
    }
    auto calc_dp = [&](int m, bool odd, bool doubling) {
        dp[0] = 1;
        for (int i = 1; i < m + doubling; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp2[j] = dp[j];
                if (j > 0) {
                    dp2[j] += dp[j - 1] * (2 * i - j + 1 - odd) * 2 % MOD;
                }
                if (j > 1) {
                    dp2[j] += dp[j - 2] * (2 * i - j + 2 - odd) % MOD * (2 * i - j + 1 - odd) % MOD;
                }
                dp2[j] %= MOD;
            }
            swap(dp, dp2);
        }
        if (!doubling) {
            for (int j = 0; j <= k; ++j) {
                dp2[j] = dp[j];
                if (j > 0) {
                    dp2[j] += dp[j - 1] * (2 * m - j + 1 - odd) % MOD;
                }
                dp2[j] %= MOD;
            }
            swap(dp, dp2);
        }
    };
    if (n & 1) {
        calc_dp((n + 1) >> 1, true, false);
        swap(dp, dp3);
        fill(dp, dp + k + 1, 0);
        calc_dp(n >> 1, false, true);
        ll ans = 0;
        for (int i = 0; i <= k; ++i) {
            ans += dp[i] * dp3[k - i] % MOD;
        }
        ans %= MOD;
        cout << ans << '\n';
    } else {
        calc_dp(n >> 1, true, true);
        ll ans = 0;
        for (int i = 0; i <= k; ++i) {
            ans += dp[i] * dp[k - i] % MOD;
        }
        ans %= MOD;
        cout << ans << '\n';
    }
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