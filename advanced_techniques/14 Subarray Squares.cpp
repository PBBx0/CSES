#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e17;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> x(n), pref(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        pref[i + 1] = pref[i] + x[i];
    }
    vector<vector<int>> opt(n + 2, vector<int>(k + 1));
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, INF));
    dp[0][0] = 0;
    for (int j = 1; j <= k; ++j) {
        opt[n + 1][j] = n - 1;
        for (int i = n; i > 0; --i) {
            for (int t = opt[i][j - 1]; t <= opt[i + 1][j]; ++t) {
                ll cur = dp[t][j - 1] + (pref[i] - pref[t]) * (pref[i] - pref[t]);
                if (dp[i][j] > cur) {
                    dp[i][j] = cur;
                    opt[i][j] = t;
                }
            }
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