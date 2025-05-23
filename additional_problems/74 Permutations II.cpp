#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    ll d[n + 10];
    d[0] = d[1] = 1;
    d[2] = d[3] = 0;
    for (ll i = 4; i <= n; ++i) {
        d[i] = (i + 1) * d[i - 1] - (i - 2) * d[i - 2] - (i - 5) * d[i - 3] + (i - 3) * d[i - 4];
        d[i] = (d[i] % MOD + MOD) % MOD;
    }
    cout << d[n] << '\n';
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