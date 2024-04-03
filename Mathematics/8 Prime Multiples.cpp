#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> p(k);
    for (ll& el : p) cin >> el;
    ll res = 0;
    for (ll mask = 1; mask < (1 << k); ++mask) {
        int cnt = 0;
        ll cur = n;
        for (int i = 0; i < k; ++i) if (mask & (1 << i)) {
            cnt++;
            cur /= p[i];
        }
        if (cnt % 2 == 0) cur = -cur;
        res += cur;
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}