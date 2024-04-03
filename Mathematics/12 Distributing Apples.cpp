#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int T = 2e6 + 1;
const ll MOD = 1e9 + 7;
ll fact[T];
ll inv(ll a) {
    ll res = 1;
    for (ll pw = MOD - 2; pw > 0; pw >>= 1) {
        if (pw & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
ll c(ll n, ll k) {
    return fact[n] * inv(fact[k]) % MOD * inv(fact[n - k]) % MOD;
}
void solve() {
    fact[0] = 1;
    for (ll i = 1; i < T; ++i) fact[i] = fact[i - 1] * i % MOD;
    ll n, m;
    cin >> n >> m;
    cout << c(n + m - 1, n - 1) << '\n';
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