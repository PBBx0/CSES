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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> dp(m + 2, 1), dp2(m + 2);
    for (int i = 0; i < n; ++i) {
        fill(all(dp2), 0);
        if (a[i] == 0) {
            for (int d = 1; d <= m; ++d) {
                dp2[d] = add(dp[d - 1], add(dp[d], dp[d + 1]));
            }
        } else {
            dp2[a[i]] = add(dp[a[i] - 1], add(dp[a[i]], dp[a[i] + 1]));
        }
        swap(dp, dp2);
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i) ans = add(ans, dp[i]);
    const int inv3 = (MOD + 1) / 3;
    cout << mul(ans, inv3) << '\n';
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