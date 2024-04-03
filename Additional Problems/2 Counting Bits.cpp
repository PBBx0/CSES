#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    ll n;
    ll sum = 0;
    cin >> n;
    n++;
    for (ll k = 1; k <= n; k <<= 1) {
        ll d = n / (k << 1);
        ll r = n % (k << 1);
        sum += d * k;
        ll add = r - min(k, r);
        sum += add;
    }
    cout << sum << '\n';
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