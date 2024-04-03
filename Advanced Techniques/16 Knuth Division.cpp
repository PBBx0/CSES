#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e17;
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n), p(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        p[i + 1] = p[i] + a[i];
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, INF)),  opt(n + 2, vector<ll>(n + 2));
    for (int i = 0; i < n; ++i) dp[i][i] = dp[i][i + 1] = 0;
    dp[n][n] = 0;
    for (int r = 2; r <= n; ++r) {
        opt[r - 1][r] = r - 1;
        for (int l = r - 2; l >= 0; --l) {
            for (ll t = opt[l][r - 1]; t <= opt[l + 1][r]; ++t) {
                ll cur = p[r] - p[l] + dp[l][t] + dp[t][r];
                if (dp[l][r] > cur) {
                    dp[l][r] = cur;
                    opt[l][r] = t;
                }
            }
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}