#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
ll pow(ll a, ll b, ll mod) {
    ll res = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}
void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    cout << pow(a, pow(b, c, MOD - 1), MOD) << '\n';
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}