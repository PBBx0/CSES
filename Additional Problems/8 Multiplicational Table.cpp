#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    ll n;
    cin >> n;
    ll lo = 0, hi = n * n;
    while (hi - lo > 1) {
        ll md = (hi - lo) / 2 + lo;
        ll cnt = 0;
        for (ll x = 1; x <= n; ++x) {
            cnt += min(n, md / x);
        }
        if (cnt * 2 >= n * n) {
            hi = md;
        } else {
            lo = md;
        }
    }
    cout << hi << '\n';
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