#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int T = 1e6 + 1;
const ll MOD = 1e9 + 7;
ll fact[T];
ll inv(ll a) {
    ll res = 1;
    for (ll p = MOD - 2; p > 0; p >>= 1) {
        if (p & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
void solve() {
    fact[0] = 1;
    for (ll i = 1; i < T; ++i) fact[i] = i * fact[i - 1] % MOD;
    ll n;
    cin >> n;
    if (n & 1) {
        cout << 0 << '\n';
        return;
    }
    ll res = fact[n] * inv(fact[n / 2]) % MOD * inv(fact[n / 2]) % MOD * inv(n / 2 + 1) % MOD;
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