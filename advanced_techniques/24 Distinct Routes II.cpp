#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct edge {
    int from, to, cap, cost, flow = 0;
    edge(int from = 0, int to = 0, int cap = 0, int cost = 0) : \
    from(from), to(to), cap(cap), cost(cost) {}
};
const int N = 500, M = 1000, INF = 1e9;
vector<int> g[N];
edge E[M * 2];
int d[N], used[N], p[N], par[N];
int n, m, k;
vector<int> paths[N];
void dfs(int v, int path_id) {
    paths[path_id].emplace_back(v);
    if (v == n - 1) {
        return;
    }
    for (int id : g[v]) {
        auto & [_, to, cp, cs, fl] = E[id];
        if (fl > 0) {
            fl--;
            dfs(to, path_id);
            return;
        }
    }
}
void solve() {
    cin >> n >> m >> k;
    int top = 0;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(top);
        E[top++] = {a, b, 1, 1};
        g[b].emplace_back(top);
        E[top++] = {b, a, 0, -1};
    }
    fill(d, d + n, INF);
    fill(par, par + n, -1);
    d[0] = 0;
    for (int _ = 0; _ < n; ++_) {
        for (int id = 0; id < top; ++id) {
            auto [from, to, cp, cs, fl] = E[id];
            if (cp == fl || d[to] <= d[from] + cs) continue;
            d[to] = d[from] + cs;
            par[to] = id;
        }
    }
    int res = 0;
    for (int _ = 0; _ < k; ++_) {
        for (int i = 0; i < n; ++i) p[i] += d[i];
        if (d[n - 1] == INF) {
            cout << -1 << '\n';
            return;
        }
        for (int v = n - 1; par[v] != -1; ) {
            int id = par[v];
            E[id].flow++;
            E[id ^ 1].flow--;
            v = E[id].from;
            res += E[id].cost;
        }
        fill(d, d + n, INF);
        fill(used, used + n, false);
        fill(par, par + n, -1);
        d[0] = 0;
        for (int i = 0; i < n; ++i) {
            int v = -1;
            for (int j = 0; j < n; ++j) {
                if (!used[j] && (v == -1 || d[v] > d[j])) v = j;
            }
            used[v] = true;
            for (int id : g[v]) {
                auto [_kek_, to, cp, cs, fl] = E[id];
                if (used[to] || cp == fl || d[to] < d[v] + cs + p[v] - p[to]) continue;
                d[to] = d[v] + cs + p[v] - p[to];
                par[to] = id;
            }
        }
    }
    cout << res << '\n';
    for (int i = 0; i < k; ++i) {
        dfs(0, i);
        cout << sz(paths[i]) << '\n';
        for (int v : paths[i]) cout << v + 1 << ' ';
        cout << '\n';
    }
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