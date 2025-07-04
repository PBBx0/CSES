#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void dfs(int v, int p, const auto& g, auto& col, auto& cur_stack) {
    col[v] = 1;
    for (int to : g[v]) {
        if (to == p) continue;
        if (col[to] == 1) {
            int id = 0;
            while (cur_stack[id] != to) ++id;
            cout << sz(cur_stack) - id + 1 << '\n';
            for (int i = id; i < sz(cur_stack); ++i) cout << cur_stack[i] + 1 << ' ';
            cout << to + 1 << '\n';
            exit(0);
        }
        cur_stack.emplace_back(to);
        dfs(to, v, g, col, cur_stack);
        cur_stack.pop_back();
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
            vector<int> cur_stack{v};
            dfs(v, v, g, col, cur_stack);
        }
    }
    cout << "IMPOSSIBLE\n";
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