#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
ll pow(ll a, ll pw) {
    ll res = 1;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
ll inv(ll a) {
    return pow(a, MOD - 2);
}
void solve() {
    ll n, k;
    cin >> n >> k;
    ll res = 0, cur = 1;
    for (ll x = 0; x < k; ++x) {
        res = (res + cur * pow(k - x, n) % MOD) % MOD;
        cur = cur * (k - x) % MOD * inv(x + 1) % MOD;
        cur = -cur;
    }
    cout << (res + MOD) % MOD << '\n';
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