#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const ll INF = 1e18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> g(n);
    vector<ll> dst(n, INF);
    vector<ll> dst2(n, INF);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        g[a].emplace_back(b, c);
    }
    set<pair<ll, int>> s;
    dst[0] = dst2[0] = 0;
    s.emplace(0, 0);
    while (!s.empty()) {
        auto [dv, v] = *s.begin();
        s.erase(s.begin());
        for (auto [to, w] : g[v]) {
            ll& x = dst[to];
            dst2[to] = min(dst2[to], dv + w / 2);
            if (x > dv + w) {
                s.erase({x, to});
                x = dv + w;
                s.emplace(x, to);
            }
        }
    }
    for (int i = 0; i < n; ++i) s.emplace(dst2[i], i);
    while (!s.empty()) {
        auto [dv, v] = *s.begin();
        s.erase(s.begin());
        for (auto [to, w] : g[v]) {
            ll& x = dst2[to];
            if (x > dv + w) {
                s.erase({x, to});
                x = dv + w;
                s.emplace(x, to);
            }
        }
    }
    cout << dst2[n - 1] << '\n';
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