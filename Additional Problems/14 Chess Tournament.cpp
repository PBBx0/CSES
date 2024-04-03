#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
void impossible() {
    cout << "IMPOSSIBLE" << '\n';
    exit(0);
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int mx = 0, sm = 0;
    for (int & el : a) {
        cin >> el;
        mx = max(mx, el);
        sm += el;
    }
    if (mx * 2 > sm || sm % 2 == 1) impossible();
    set<pair<int, int>> b;
    for (int i = 0; i < n; ++i) {
        if (a[i]) b.emplace(a[i], i);
    }
    vector<pair<int, int>> ans;
    while (!b.empty()) {
        auto [x, id] = *b.rbegin();
        b.erase(--b.end());
        if (x > sz(b)) impossible();
        vector<pair<int, int>> tmp;
        for (int i = 0; i < x; ++i) {
            auto [y, id2] = *b.rbegin();
            b.erase(--b.end());
            ans.emplace_back(id, id2);
            tmp.emplace_back(--y, id2);
        }
        for (auto [y, id2] : tmp) {
            if (y) b.emplace(y, id2);
        }
    }
    cout << sz(ans) << '\n';
    for (auto [i, j] : ans) cout << i + 1 << ' ' << j + 1 << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}