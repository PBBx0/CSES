#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

vector<vector<int>> g;
vector<int> col, dp, comp, tin, st;
int timer = 0, comp_color = 0;

void dfs(int v) {
    col[v] = 1;
    tin[v] = timer++;
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
            comp[u] = comp_color;
            st.pop_back();
            if (u == v) break;
        }
        ++comp_color;
    }
    col[v] = 2;
}

void solve() {
    int n, m;
    cin >> m >> n;
    g.resize(n << 1), tin.resize(n << 1), col.resize(n << 1), comp.resize(n << 1, -1), dp.resize(n << 1);
    for (int i = 0; i < m; ++i) {
        char c1, c2;
        int a1, a2;
        cin >> c1 >> a1 >> c2 >> a2;
        a1 = (a1 - 1) << 1 | (c1 == '-');
        a2 = (a2 - 1) << 1 | (c2 == '-');
        g[a1 ^ 1].emplace_back(a2);
        g[a2 ^ 1].emplace_back(a1);
    }
    for (int i = 0; i < 2 * n; ++i) {
        if (col[i] == 0) dfs(i);
    }
    for (int i = 0; i < n; ++i) {
        if (comp[i << 1] == comp[i << 1 | 1]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    vector<vector<int>> cvtx(comp_color);
    for (int i = 0; i < (n << 1); ++i) {
        cvtx[comp[i]].emplace_back(i);
    }
    vector<int> used(n, -1);
    for (int c = comp_color - 1; c >= 0; --c) {
        bool ok = true;
        for (int v : cvtx[c]) {
            ok &= used[v >> 1] == -1;
        }
        for (int v : cvtx[c]) {
            used[v >> 1] = ok ^ (v & 1);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << (used[i] == 0 ? '+' : '-') << ' ';
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