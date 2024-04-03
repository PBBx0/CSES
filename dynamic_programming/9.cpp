#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e6 + 5, MOD = 1e9 + 7;
ll dp1[N], dp2[N];
void solve() {
    dp1[1] = dp2[1] = 1;
    for (int i = 2; i < N; ++i) {
        dp1[i] = (2LL * dp1[i - 1] + dp2[i - 1]) % MOD;
        dp2[i] = (4LL * dp2[i - 1] + dp1[i - 1]) % MOD;
    }
    int tt;
    cin >> tt;
    while (tt--) {
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
    solve();
    return 0;
}