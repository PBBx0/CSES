#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    ll n;
    cin >> n;
    auto f = [](ll x) {
        return x & 1 ? x * 3 + 1 : x >> 1;
    };
    while (1) {
        cout << n << ' ';
        if (n == 1) break;
        n = f(n);
    }
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