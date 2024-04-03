#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N], rg[N], vts, zg[N + 1];
int col[N], used[N];
ll cost[N], zcost[N + 1];
void dfs(int v) {
    col[v] = 0;
    for (int to : g[v]) if (col[to] == -1) {
        dfs(to);
    }
    vts.emplace_back(v);
}
void paint_comp(int v, int c) {
    col[v] = c;
    zcost[c] += cost[v];
    for (int to : rg[v]) if (col[to] == 0) {
        paint_comp(to, c);
    }
}
ll calc_cost(int v) {
    if (used[v]) return zcost[v];
    used[v] = true;
    ll x = zcost[v];
    for (int to : zg[v]) {
        zcost[v] = max(zcost[v], x + calc_cost(to));
    }
    return zcost[v];
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> cost[i];
    fill(col, col + n, -1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        rg[b].emplace_back(a);
    }
    for (int v = 0; v < n; ++v) if (col[v] == -1) {
        dfs(v);
    }
    std::reverse(vts.begin(), vts.end());
    int c = 0;
    for (int v : vts) if (col[v] == 0) {
        paint_comp(v, ++c);
    }
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) {
            if (col[v] != col[to]) zg[col[v]].emplace_back(col[to]);
        }
    }
    ll res = 0;
    for (int i = 1; i <= c; ++i) {
        res = max(res, calc_cost(i));
    }
    cout << res << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}