#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int A = 5020, N = 101;
const ll MOD = 1e9 + 7;
ll dp[N][A + A + 1], dp2[N][A + A + 1];
void solve() {
    ll n, x;
    cin >> n >> x;
    ll a[n];
    for (ll & el : a) cin >> el;
    sort(a, a + n);
    dp[0][A] = 1;
    for (ll v : a) {
        for (ll cnt = 0; cnt < n; ++cnt) {
            for (ll k = 0; k < A + A + 1; ++k) {
                dp2[cnt][k] = (cnt + 1) * dp[cnt][k] % MOD;
                if (k >= v) dp2[cnt][k] += (cnt + 1) * dp[cnt + 1][k - v] % MOD;
                if (cnt && k + v <= A + A) dp2[cnt][k] += dp[cnt - 1][k + v];
                dp2[cnt][k] %= MOD;
            }
        }
        swap(dp, dp2);
    }
    ll res = 0;
    for (ll t = A; t <= x + A; ++t) res += dp[0][t];
    cout << res % MOD << '\n';
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