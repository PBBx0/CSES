#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void dfs(int v, const auto& g, auto& used) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) dfs(to, g, used);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    vector<bool> used(n, false);
    vector<int> comps;
    for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            dfs(v, g, used);
            if (v != 0) comps.emplace_back(v);
        }
    }
    cout << sz(comps) << '\n';
    for (int el : comps) cout << 1 << ' ' << el + 1 << '\n';
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