#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

bool ok = true;

void dfs(int v, int cur_col, const auto& g, auto& col) {
    col[v] = cur_col;
    for (int to : g[v]) {
        if (col[to] == cur_col) {
            ok = false;
            return;
        }
        if (col[to] == 0) dfs(to, 3 - cur_col, g, col);
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
    vector<int> col(n, 0);
    for (int v = 0; v < n; ++v) {
        if (col[v] == 0) {
            dfs(v, 1, g, col);
        }
    }
    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (int i = 0; i < n; ++i) {
        cout << col[i] << ' ';
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