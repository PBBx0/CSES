#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int INF = 1e9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector dp(n + 1, vector<int>(m + 1, INF));
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) {
        if (i == j) {
            dp[i][j] = 0;
            continue;
        }
        for (int i1 = 1; i1 < i; ++i1) dp[i][j] = min(dp[i][j], dp[i1][j] + 1 + dp[i - i1][j]);
        for (int j1 = 1; j1 < j; ++j1) dp[i][j] = min(dp[i][j], dp[i][j1] + 1 + dp[i][j - j1]);
    }
    cout << dp[n][m] << '\n';
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