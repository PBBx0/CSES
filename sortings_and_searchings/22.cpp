#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n), d(n);
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> d[i];
        res += d[i];
    }
    sort(a.begin(), a.end());
    for (ll cur = 0, i = 0; i < n; cur += a[i++]) {
        res -= (cur + a[i]);
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