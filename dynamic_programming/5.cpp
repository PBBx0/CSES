#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
inline ll maxd(ll x) {
    ll res = 0;
    for (; x > 0; x /= 10) res = max(res, x % 10);
    return res;
}
void solve() {
    ll n;
    cin >> n;
    ll dp[n + 1];
    dp[0] = 0;
    for (ll x = 1; x <= n; ++x) dp[x] = 1 + dp[x - maxd(x)];
    cout << dp[n] << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    solve();
    return 0;
}