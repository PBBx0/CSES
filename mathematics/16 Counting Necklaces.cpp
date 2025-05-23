#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
ll pw(ll a, ll pw) {
    ll res = 1;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
ll inv(ll a) {
    return pw(a, MOD - 2);
}
void solve() {
    ll n, m;
    cin >> n >> m;
    ll dp[n + 1];
    dp[1] = m;
    ll res = m;
    for (ll x = 2; x <= n; ++x) if (n % x == 0) {
        dp[x] = (pw(m, x) - m + MOD) % MOD;
        for (ll d = 2; d * d <= x; ++d) {
            if (x % d == 0) {
                dp[x] = (dp[x] - dp[d] + MOD) % MOD;
                if (d * d != x) {
                    dp[x] = (dp[x] - dp[x / d] + MOD) % MOD;
                }
            }
        }
        res += dp[x] * inv(x) % MOD;
        res %= MOD;
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}