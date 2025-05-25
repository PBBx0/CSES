#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &el: a) cin >> el;
    vector<ll> pref(n + 1);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];
    auto get_sum = [&](int l, int r) {
        return pref[r] - pref[l];
    };
    vector dp(n + 1, vector<ll>(n + 1, 0));
    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            dp[i][i + len] = max(a[i] + get_sum(i + 1, i + len) - dp[i + 1][i + len],
                                 a[i + len - 1] + get_sum(i, i + len - 1) - dp[i][i + len - 1]);
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}