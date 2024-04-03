#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 500, M = 2000, INF = 1e9 + 7;
struct edge {
    int from, to, cap, flow = 0;
    edge(int a = 0, int b = 0, int c = 0) : from(a), to(b), cap(c) {}
};
edge E[M];
vector<int> g[N];
int d[N], par[N], n;
int bfs(int v0, int cc) {
    fill(d, d + n, -1);
    d[v0] = 0;
    vector<int> q{v0};
    for (int st = 0; st < sz(q); ++st) {
        int v = q[st];
        for (int id : g[v]) {
            auto [_, to, cp, fl] = E[id];
            if (d[to] != -1 || cp - fl < cc) continue;
            d[to] = d[v] + 1;
            par[to] = id;
            q.emplace_back(to);
        }
    }
    if (d[n - 1] == -1) return 0;
    int min_c = INF;
    for (int v = n - 1; v != v0; ) {
        auto [from, _, cp, fl] = E[par[v]];
        min_c = min(min_c, cp - fl);
        v = from;
    }
    for (int v = n - 1; v != v0; ) {
        int id = par[v];
        E[id].flow += min_c;
        E[id ^ 1].flow -= min_c;
        v = E[id].from;
    }
    return min_c;
}
int edmonds_karp() {
    int flow = 0;
    for (int c = INF; c > 0; c >>= 1) {
        while (int pushed = bfs(0, c))
            flow += pushed;
    }
    return flow;
}
vector<vector<int>> out;
void dfs(int v) {
    if (v == n - 1) {
        out.back().emplace_back(v);
        return;
    }
    for (int i : g[v]) {
        auto& [_, to, cp, fl] = E[i];
        if (fl > 0) {
            fl--;
            out.back().emplace_back(v);
            dfs(to);
            return;
        }
    }
}
void restore_flow(int v0 = 0) {
    for (int i : g[v0]) {
        for (auto& [_, to, cp, fl] = E[i]; fl > 0; fl--) {
            out.emplace_back();
            out.back().emplace_back(v0);
            dfs(to);
        }
    }
}
void solve() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        E[i * 2] = edge(a, b, 1);
        E[i * 2 + 1] = edge(b, a, 0);
        g[a].emplace_back(2 * i);
        g[b].emplace_back(2 * i + 1);
    }
    cout << edmonds_karp() << '\n';
    restore_flow();
    for (auto& a : out) {
        cout << sz(a) << '\n';
        for (int el : a) cout << el + 1 << ' ';
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