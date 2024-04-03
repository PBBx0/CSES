#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    multiset<int> prices;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        prices.insert(x);
    }
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        auto it = prices.upper_bound(t);
        if (it == prices.begin()) {
            cout << -1 << '\n';
        } else {
            --it;
            cout << *it << '\n';
            prices.erase(it);
        }
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}