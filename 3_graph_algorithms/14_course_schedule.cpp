#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

vector<vector<int>> g;
vector<int> col, order;

void dfs(int v) {
    col[v] = 1;
    for (int to : g[v]) {
        if (col[to] == 1) {
            cout << "IMPOSSIBLE\n";
            exit(EXIT_SUCCESS);
        }
        if (col[to] == 0) {
            dfs(to);
        }
    }
    order.emplace_back(v);
    col[v] = 2;
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    col.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[b].emplace_back(a);
    }
    for (int i = 0; i < n; ++i) if (col[i] == 0) dfs(i);
    for (int el : order) cout << el + 1 << ' ';
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