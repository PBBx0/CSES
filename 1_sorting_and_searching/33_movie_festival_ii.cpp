#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for (auto &[l, r]: a) cin >> l >> r;
    sort(all(a), [](auto lhs, auto rhs) { return lhs.second < rhs.second; });
    multiset<int> mem;
    for (int i = 0; i < k; ++i) mem.emplace(0);
    int ans = 0;
    for (auto [l, r] : a) {
        auto iter = mem.upper_bound(l);
        if (iter != mem.begin()) {
            mem.erase(--iter);
            ++ans;
            mem.emplace(r);
        }
    }
    cout << ans << '\n';
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