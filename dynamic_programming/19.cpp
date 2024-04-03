#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
#define int ll
using namespace std;

using ll = int64_t;
const int T = 20, D = 10, MOD = 1e9 + 7;
ll cnt(ll x) {
    if (x < 0) return 0;
    if (x == 0) return 1;
    vector<int> digits;
    for (int t = x; t > 0; t /= 10) digits.emplace_back(t % 10);
    while (sz(digits) < T) digits.emplace_back(0);
    reverse(digits.begin(), digits.end());
    array<array<int, D>, T> dp{};
    array<bool, T> dp_mx{};
    int i = 0;
    while (!digits[i]) ++i;
    for (int d = 0; d < digits[i]; ++d) {
        dp[i][d] = 1;
        dp_mx[i] = true;
    }
    for (i++; i < T; ++i) {
        for (int d = 0; d < D; ++d) {
            for (int d2 = 0; d2 < D; ++d2) if (d != d2) {
                dp[i][d] += dp[i - 1][d2];
            }
        }
        for (int d = 0; d < digits[i]; ++d) if (d != digits[i - 1]) {
            dp[i][d] += dp_mx[i - 1];
        }
        dp_mx[i] = dp_mx[i - 1] && digits[i - 1] != digits[i];
        dp[i][0]++;
    }
    ll res = dp_mx[T - 1];
    for (int d = 0; d < D; ++d) {
        res += dp[T - 1][d];
    }
    return res;
}

void solve() {
    ll a, b;
    cin >> a >> b;
    cout << cnt(b) - cnt(a - 1) << '\n';
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