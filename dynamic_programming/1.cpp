#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e6 + 10, MOD = 1e9 + 7;
int dp[N];
void solve() {
    int n;
    cin >> n;
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int x = 1; x <= 6; ++x) {
            dp[i + x] = (dp[i + x] + dp[i]) % MOD;
        }
    }
    cout << dp[n] << '\n';
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