#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

ll count_less_than_R(ll R) {
    if (R == 0) return 0;
    vector<int> digitsR;
    for (ll t = R; t; t /= 10) digitsR.emplace_back(t % 10);
    reverse(all(digitsR));
    int n = sz(digitsR);
    vector dp(n, array<array<ll, 10>, 3>{});
    dp[0][0][0] = 1;
    dp[0][2][digitsR[0]] = 1;
    for (int d = 1; d < digitsR[0]; ++d) dp[0][1][d] = 1;

    for (int i = 0; i + 1 < n; ++i) {
        dp[i + 1][0][0] = 1;
        for (int d1 = 0; d1 < 10; ++d1) for (int d2 = 0; d2 < 10; ++d2) {
            if (d1 == d2) continue;
            dp[i + 1][1][d2] += dp[i][1][d1];
        }
        for (int d2 = 1; d2 < 10; ++d2) {
            dp[i + 1][1][d2] += dp[i][0][0];
        }
        for (int d1 = digitsR[i], d2 = 0; d2 < digitsR[i + 1]; ++d2) {
            if (d1 == d2) continue;
            dp[i + 1][1][d2] += dp[i][2][d1];
        }
        {
            int d1 = digitsR[i], d2 = digitsR[i + 1];
            if (d1 != d2) dp[i + 1][2][d2] += dp[i][2][d1];
        }
    }

    return std::accumulate(all(dp[n - 1][1]), 0LL) + 1;
}

void solve() {
    ll a, b;
    cin >> a >> b;
    cout << count_less_than_R(b + 1) - count_less_than_R(a) << '\n';
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