#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int L, n;
    cin >> L >> n;
    set<pair<int, int>> s;
    s.emplace(1, L + 1);
    multiset<int> lens;
    lens.emplace(L);

    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        auto iter = --s.upper_bound({p, L * 2});
        auto [l, r] = *iter;
        s.erase(iter);
        lens.erase(lens.find(r - l));
        if (l < p + 1) {
            s.emplace(l, p + 1);
            lens.emplace(p + 1 - l);
        }
        if (p + 1 < r) {
            s.emplace(p + 1, r);
            lens.emplace(r - p - 1);
        }
        cout << *lens.rbegin() << ' ';
    }
    cout << '\n';
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