#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int MOD = 1e9 + 7;

void solve() {
    const int N = 1e6 + 10;
    vector<ll> dp1(N), dp2(N);
    dp1[1] = dp2[1] = 1;
    for (int i = 2; i < N; ++i) {
        dp1[i] = (2 * dp1[i - 1] + dp2[i - 1]) % MOD;
        dp2[i] = (4 * dp2[i - 1] + dp1[i - 1]) % MOD;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << (dp1[n] + dp2[n]) % MOD << '\n';
    }
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