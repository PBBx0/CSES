#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int A = 1e5 + 69;
ll bp[A];
void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> w(n), c(n);
    for (int& el : w) cin >> el;
    for (int& el : c) cin >> el;
    for (int i = 0; i < n; ++i) {
        for (int t = x - w[i]; t >= 0; --t) {
            bp[t + w[i]] = max(bp[t + w[i]], bp[t] + c[i]);
        }
    }
    ll res = 0;
    for (int i = 0; i <= x; ++i) {
        res = max(res, bp[i]);
    }
    cout << res << '\n';
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