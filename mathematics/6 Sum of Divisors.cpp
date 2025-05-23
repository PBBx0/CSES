#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
void solve() {
    ll n;
    cin >> n;
    ll k = 2e6;
    ll res = 0;
    for (ll d = 1; d <= k; ++d) {
        if (n / d > k) {
            res += d * (n / d) % MOD;
        }
        ll hi = n / d, lo = n / (d + 1);
        ll a = (hi + lo + 1) % MOD, b = (hi - lo) % MOD;
        ll inv2 = MOD / 2 + 1;
        ll c = (((a * b) % MOD) * inv2) % MOD;
        res += (c * d) % MOD;
        res %= MOD;
    }
    cout << res << '\n';
}

signed main() {
    int tt = 1;
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    cin >> tt;
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    while (tt--) solve();
    return 0;
}