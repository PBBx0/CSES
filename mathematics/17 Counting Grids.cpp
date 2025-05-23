#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
ll pw(ll a, ll pw) {
    ll res = 1;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
ll inv(ll a) {
    return pw(a, MOD - 2);
}
void solve() {
    ll n;
    cin >> n;
    ll n2 = n * n;
    ll res = (pw(2, n2) + pw(2, (n2 + 1) / 2) + pw(2, (n2 + 7) / 4)) % MOD;
    res = res * inv(4) % MOD;
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