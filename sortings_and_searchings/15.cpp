#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int x, n;
    cin >> x >> n;
    multiset<int> dist{x};
    set<pair<int, int>> bds{{1, x + 1}};
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        auto it = bds.upper_bound({p, x + x});
        if (it == bds.begin()) continue;
        --it;
        auto [l, r] = *it;
        bds.erase(it);
        dist.erase(dist.find(r - l));
        if (p + 1 - l) {
            dist.insert(p + 1 - l);
            bds.insert({l, p + 1});
        }
        if (r - p - 1) {
            dist.insert(r - p - 1);
            bds.insert({p + 1, r});
        }
        cout << *dist.rbegin() << '\n';
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