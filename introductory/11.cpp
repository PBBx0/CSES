#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    ll a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);
    if ((a + b) % 3 == 0 && 2 * a >= b) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}