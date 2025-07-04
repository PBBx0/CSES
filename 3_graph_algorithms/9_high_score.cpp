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
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        g[a].emplace_back(b, c);
    }
    vector<ll> cost(n, -INF);
    vector<bool> from_0(n), to_n(n), in_cycle(n);
    from_0[0] = to_n[n - 1] = true;
    cost[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int v = 0; v < n; ++v) for (auto [to, w] : g[v]) {
            if (cost[to] < cost[v] + w) {
                cost[to] = cost[v] + w;
            }
            if (from_0[v]) from_0[to] = true;
            if (to_n[to]) to_n[v] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int v = 0; v < n; ++v) for (auto [to, w] : g[v]) {
            if (cost[to] < cost[v] + w) {
                cost[to] = cost[v] + w;
                in_cycle[to] = true;
            }
        }
    }
    for (int v = 0; v < n; ++v) {
        if (from_0[v] && in_cycle[v] && to_n[v]) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << cost[n - 1] << '\n';
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