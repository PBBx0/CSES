#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
using ld = long double;
const int N = 101;
ld dp[N];
const ld ONE = 1.;
void solve() {
    int n;
    cin >> n;
    vector<ld> r(n);
    for (ld & el : r) cin >> el;
    ld res = 0;
    for (int i = 0; i < n; ++i) {
        ld cur = 0;
        for (int d = 1; d <= r[i]; ++d) {
            for (int x = d + 1; x < N; ++x) cur += dp[x];
        }
        res += cur / r[i];
        for (int d = 1; d <= r[i]; ++d) dp[d] += ONE / r[i];
    }
    cout << fixed << setprecision(6);
    cout << res << '\n';

}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}