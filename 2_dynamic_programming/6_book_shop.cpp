#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<ll> bp(x + 1);
    vector<int> w(n), c(n);
    for (int& el : w) cin >> el;
    for (int& el : c) cin >> el;
    for (int i = 0; i < n; ++i) {
        for (int d = x; d - w[i] >= 0; --d) bp[d] = max(bp[d - w[i]] + c[i], bp[d]);
    }
    cout << bp[x] << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}