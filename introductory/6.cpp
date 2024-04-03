#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    ll x, y;
    cin >> y >> x;
    --x, --y;
    if (y <= x) {
        if (x & 1) {
            cout << x * x + y + 1 << '\n';
        } else {
            cout << (x + 1) * (x + 1) - y << '\n';
        }
    } else {
        if (y & 1) {
            cout << (y + 1) * (y + 1) - x << '\n';
        } else {
            cout << y * y + x + 1 << '\n';
        }
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
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}