#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    ll n, t;
    cin >> n >> t;
    vector<ll> k(n);
    for (ll& el : k) cin >> el;
    ll lo = 0, hi = 1e18;
    while (hi > lo + 1) {
        ll md = lo + hi >> 1;
        ll cur = 0;
        for (ll el : k) {
            cur += md / el;
            if (cur >= t) break;
        }
        if (cur >= t) {
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}