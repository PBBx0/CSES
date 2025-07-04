#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

vector<vector<int>> g;
vector<int> comp, dp, st, tin, col;
int timer = 0;
int comp_col = 0;

void dfs(int v) {
    tin[v] = timer++;
    col[v] = 1;
    st.emplace_back(v);

    dp[v] = tin[v];
    for (int to : g[v]) {
        if (col[to] == 0) {
            dfs(to);
            dp[v] = min(dp[v], dp[to]);
        } else if (col[to] == 1) {
            dp[v] = min(dp[v], tin[to]);
        } else if (comp[to] == -1) {
            dp[v] = min(dp[v], dp[to]);
        }
    }
    if (dp[v] == tin[v]) {
        for (;;) {
            int u = st.back();
            st.pop_back();
            comp[u] = comp_col;
            if (u == v) break;
        }
        ++comp_col;
    }
    col[v] = 2;
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n), comp.resize(n, -1), dp.resize(n), tin.resize(n), col.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
    }
    for (int v = 0; v < n; ++v) {
        if (col[v] == 0) {
            dfs(v);
        }
    }
    cout << comp_col << '\n';
    for (int i = 0; i < n; ++i) {
        cout << comp[i] + 1 << ' ';
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