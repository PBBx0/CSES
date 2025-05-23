#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

void solve() {
    ll k;
    cin >> k; --k;
    ll len = 1, cnt = 9;
    while (k >= cnt * len) {
        k -= cnt * len;
        cnt *= 10;
        ++len;
    }
    ll num = cnt / 9 + k / len;
    cout << to_string(num)[k % len] << '\n';
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