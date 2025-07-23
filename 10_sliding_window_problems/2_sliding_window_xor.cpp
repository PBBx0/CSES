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

void solve() {
    int n, k;
    cin >> n >> k;
    ll x;
    int a, b, c;
    cin >> x >> a >> b >> c;

    deque<ll> arr{x};
    auto nxt = [a, b, c](ll x) {
        return (x * a + b) % c;
    };
    for (int i = 1; i < k; ++i) {
        arr.emplace_back(nxt(arr.back()));
    }
    ll ans = 0;
    ll cur = accumulate(all(arr), (ll)0, bit_xor<ll>{});
    for (int i = 0; i <= n - k; ++i) {
        ans ^= cur;
        arr.emplace_back(nxt(arr.back()));
        cur ^= arr.front();
        cur ^= arr.back();
        arr.pop_front();
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
