#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int INF = 1e9;

void solve() {
    string s, t;
    cin >> s >> t;
    int n = sz(s), m = sz(t);
    vector dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 && j == 0) continue;
            int x = INF;
            if (i > 0) x = min(x, dp[i - 1][j] + 1);
            if (j > 0) x = min(x, dp[i][j - 1] + 1);
            if (i > 0 && j > 0) x = min(x, dp[i - 1][j - 1] + int(s[i - 1] != t[j - 1]));
            dp[i][j] = x;
        }
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