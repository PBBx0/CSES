#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
ll pow(ll a, ll k) {
    ll res = 1;
    for (; k > 0; k >>= 1) {
        if (k & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
    }
    return res;
}
void solve() {
    bool square = true;
    int n;
    cin >> n;
    ll full = 1, sqrt = 1;
    ll cnt_mod = 1, cnt_mod2 = 1, cnt_mod3 = 1;
    bool useless = true;
    ll sum = 1;
    for (int i = 0; i < n; ++i) {
        ll p, k;
        cin >> p >> k;
        square &= k % 2 == 0;
        full = full * pow(p, k) % MOD;
        sqrt = sqrt * pow(p, k >> 1) % MOD;
        cnt_mod = cnt_mod * (k + 1) % MOD;
        cnt_mod2 = cnt_mod2 * (k + 1) % (MOD - 1);
        if (k % 2 == 1 && useless) {
            cnt_mod3 = cnt_mod3 * ((k + 1) / 2) % (MOD - 1);
            useless = false;
        } else {
            cnt_mod3 = cnt_mod3 * (k + 1) % (MOD - 1);
        }
        sum  = ((sum * (pow(p, k + 1) - 1)) % MOD) * pow(p - 1, MOD - 2) % MOD;
    }
    cout << cnt_mod << ' ' << sum << ' ';
    ll prod;
    if (square) {
        prod = pow(sqrt, cnt_mod2);
    } else {
        prod = pow(full, cnt_mod3);
    }
    cout << prod << '\n';
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