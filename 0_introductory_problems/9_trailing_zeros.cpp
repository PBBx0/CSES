#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    ll n;
    cin >> n;
    ll res = 0;
    for (ll x = 5; x <= n; x *= 5) {
        res += n / x;
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