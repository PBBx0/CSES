#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    ll res = 1, a = 2;
    for (; n > 0; n >>= 1) {
        if (n & 1) {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
    }
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}