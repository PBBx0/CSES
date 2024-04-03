#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct edge {
    int from, to, cap, flow = 0;
    edge(int from = 0, int to = 0, int cap = 0) : \
    from(from), to(to), cap(cap) {}
};
const int M = 2000, N = 500, INF = 1e9 + 7;
edge E[M];
vector<int> g[N];
int n;
int d[N], ptr[N];
bool bfs(int v0 = 0, int cc = 1) {
    fill(d, d + n, -1);
    d[v0] = 0;
    vector<int> q{v0};
    for (int st = 0; st < sz(q); ++st) {
        int v = q[st];
        for (int id : g[v]) {
            auto [_, to, cp, fl] = E[id];
            if (d[to] != -1 || cp - fl < cc) continue;
            d[to] = d[v] + 1;
            q.emplace_back(to);
        }
    }
    return d[n - 1] != -1;
}
int dfs(int v, int flow, int cc = 1) {
    if (v == n - 1 || !flow) return flow;
    for (; ptr[v] < sz(g[v]); ++ptr[v]) {
        auto [_, to, cp, fl] = E[g[v][ptr[v]]];
        if (d[to] != d[v] + 1 || cp - fl < cc) continue;
        int pushed = dfs(to, min(flow, cp - fl), cc);
        if (pushed) {
            int id = g[v][ptr[v]];
            E[id].flow += pushed;
            E[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}
ll dinic() {
    ll flow = 0;
    for (int c = INF; c > 0; c >>= 1) {
        while (bfs(0, c)) {
            fill(ptr, ptr + n, 0);
            while (int pushed = dfs(0, INF, c))
                flow += pushed;
        }
    }
    return flow;
}
int col[N];
void restore_cut(int v) {
    col[v] = 1;
    for (int id : g[v]) {
        auto [_, to, cp, fl] = E[id];
        if (col[to] == 0 && cp > fl) {
            restore_cut(to);
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
        E[i * 2 + 1] = edge(b, a, 1);
        g[a].emplace_back(i * 2);
        g[b].emplace_back(i * 2 + 1);
    }
    cout << dinic() << '\n';
    restore_cut(0);
    for (int i = 0; i < 2 * m; ++i) {
        auto [from, to, cp, fl] = E[i];
        if (col[from] == 1 && col[to] == 0 && cp == fl) {
            if (i & 1) swap(from, to);
            cout << from + 1 << ' ' << to + 1 << '\n';
        }
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