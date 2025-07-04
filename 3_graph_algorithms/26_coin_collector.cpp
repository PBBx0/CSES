#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

vector<vector<int>> g, zg;
vector<int> col, comp, tin, dp, st;

int comp_col = 0, timer = 0;

void tarjan(int v) {
    col[v] = 1;
    dp[v] = tin[v] = timer++;
    st.emplace_back(v);
    for (int to : g[v]) {
        if (col[to] == 0) {
            tarjan(to);
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

vector<ll> cost;
vector<ll> dp2;

void dfs(int v) {
    dp2[v] = cost[v];
    for (int to : zg[v]) {
        if (dp2[to] == 0) dfs(to);
        dp2[v] = max(dp2[v], dp2[to] + cost[v]);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> coins(n);
    g.resize(n), col.resize(n), tin.resize(n), dp.resize(n), comp.resize(n, -1);
    for (int& el : coins) cin >> el;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
    }
    for (int v = 0; v < n; ++v) {
        if (col[v] == 0) tarjan(v);
    }
    cost.resize(comp_col);
    vector<vector<int>> cvtx(comp_col);
    zg.resize(comp_col);
    for (int i = 0; i < n; ++i) {
        cost[comp[i]] += coins[i];
        cvtx[comp[i]].emplace_back(i);
    }
    for (int i = 0; i < comp_col; ++i) {
        vector<int> edges;
        for (int v : cvtx[i]) for (int to : g[v]) edges.emplace_back(comp[to]);
        sort(all(edges));
        edges.erase(unique(all(edges)), edges.end());
        for (int el : edges) if (i != el) zg[i].emplace_back(el);
    }
    dp2.resize(comp_col, 0);
    ll mx = 0;
    for (int i = 0; i < comp_col; ++i) {
        if (dp2[i] == 0) dfs(i);
        mx = max(mx, dp2[i]);
    }
    cout << mx << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
