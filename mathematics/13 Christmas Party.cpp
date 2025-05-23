#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
void solve() {
    ll n;
    cin >> n;
    ll r = n & 1 ? -1 : 1;
    ll cur = 1;
    ll res = r;
    for (ll x = n; x > 0; --x) {
        r = -r;
        cur = cur * x % MOD;
        res = (res + r * cur) % MOD;
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