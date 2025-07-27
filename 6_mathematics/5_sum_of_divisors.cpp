#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

const ll T = 1e6 + 1;

const ll MOD = 1e9 + 7;

const ll INV2 = (MOD + 1) / 2;

void solve() {
    ll n;
    cin >> n;
    ll ans = 0;
    for (ll x = 1; x <= T; ++x) {
        if (n / x > T) {
            ans += (n / x) * x % MOD;
        }
        // n / t == x
        // t * x <= n < t * (x + 1)
        ll lo = n / (x + 1);
        ll hi = n / x;
        ll p1 = (lo + hi + 1) % MOD;
        ll p2 = (hi - lo) % MOD;
        ll sm = p1 * p2 % MOD * INV2 % MOD;
        ans += sm * x % MOD;
        ans %= MOD;
    }
    cout << ans << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
