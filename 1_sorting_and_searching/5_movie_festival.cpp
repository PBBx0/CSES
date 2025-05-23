#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> seg(n);
    for (auto& [l, r] : seg) cin >> l >> r;
    sort(all(seg), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    int ans = 0;
    int last = -1e9;
    for (auto [l, r] : seg) {
        if (l >= last) {
            ++ans, last = r;
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