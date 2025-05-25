#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int& el : a) cin >> el;
    for (int& el : b) cin >> el;
    vector dp(n + 1, vector<int>(m + 1, -1));
    dp[0][0] = 0;
    vector par(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 && j == 0) continue;
            if (i > 0 && dp[i - 1][j] > dp[i][j]) {
                dp[i][j] = dp[i - 1][j];
                par[i][j] = 0;
            }
            if (j > 0 && dp[i][j - 1] > dp[i][j]) {
                dp[i][j] = dp[i][j - 1];
                par[i][j] = 1;
            }
            if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                par[i][j] = 2;
            }
        }
    }
    cout << dp[n][m] << '\n';
    vector<int> output;
    for (int i = n, j = m; i > 0 || j > 0;) {
        switch (par[i][j]) {
            case 0:
                i -= 1;
                break;
            case 1:
                j -= 1;
                break;
            case 2:
                i -= 1, j -= 1;
                output.emplace_back(a[i]);
        }
    }
    reverse(all(output));
    for (int el : output) cout << el << ' ';
    cout << '\n';
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