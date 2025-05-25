#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int MOD = 1e9 + 7;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<string> field(n);
    for (auto& el : field) cin >> el;
    if (field[0][0] == '*' || field[n - 1][n - 1] == '*') {
        cout << 0 << '\n';
        return;
    }
    vector dp(n, vector<int>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (field[i][j] == '*') continue;
        if (i > 0) dp[i][j] = add(dp[i][j], dp[i - 1][j]);
        if (j > 0) dp[i][j] = add(dp[i][j], dp[i][j - 1]);
    }
    cout << dp[n - 1][n - 1] << '\n';
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