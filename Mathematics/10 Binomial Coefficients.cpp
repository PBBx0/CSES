#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e6 + 1;
const ll MOD = 1e9 + 7;
ll fact[N], infact[N];
ll inv(ll x) {
    ll res = 1;
    for (ll pw = MOD - 2; pw > 0; pw >>= 1) {
        if (pw & 1) res = res * x % MOD;
        x = x * x % MOD;
    }
    return res;
}
void solve() {
    fact[0] = fact[1] = 1;
    for (ll i = 2; i < N; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    infact[N - 1] = inv(fact[N - 1]);
    for (ll i = N - 2; i >= 0; --i) {
        infact[i] = infact[i + 1] * (i + 1) % MOD;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll a, b;
        cin >> a >> b;
        ll res = fact[a] * infact[b] % MOD * infact[a - b] % MOD;
        cout << res << '\n';
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
//    cin >> tt;
    while (tt--) solve();
    return 0;
}