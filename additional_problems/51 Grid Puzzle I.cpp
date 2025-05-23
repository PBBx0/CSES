#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct edge {
    int from, to, cap, flow;
    edge(int from = 0, int to = 0, int c = 0, int f = 0) : \
    from(from), to(to), cap(c), flow(f) {}
};
const int N = 50, M = 6000, N2 = N + N + 2, INF = 1e9 + 1000 - 7;
edge E[M];
vector<int> g[N2];
int d[N2], ptr[N2];
int n, start, targ;
bool bfs(int cc) {
    fill(d, d + N2, INF);
    d[start] = 0;
    vector<int> q{start};
    for (int st = 0; st < sz(q); ++st) {
        int v = q[st];
        for (int id : g[v]) {
            auto [_, to, cp, fl] = E[id];
            if (d[to] != INF || cp - fl < cc) continue;
            d[to] = d[v] + 1;
            q.emplace_back(to);
        }
    }
    return d[targ] != INF;
}
int dfs(int v, int flow, int cc) {
    if (v == targ || !flow) return flow;
    for (int & i = ptr[v]; i < sz(g[v]); ++i) {
        auto [_, to, cp, fl] = E[g[v][i]];
        if (d[to] != d[v] + 1 || cp - fl < cc) continue;
        if (int pushed = dfs(to, min(flow, cp - fl), cc)) {
            E[g[v][i]].flow += pushed;
            E[g[v][i] ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}
int dinic() {
    int res = 0;
    for (int c = INF; c > 0; c >>= 1) {
        while (bfs(c)) {
            fill(ptr, ptr + N2, 0);
            while (int pushed = dfs(start, INF, c)) res += pushed;
        }
    }
    return res;
}
int ans[N][N];
void solve() {
    cin >> n;
    start = 0, targ = n + n + 1;
    int top = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = n + 1; j <= n + n; ++j) {
            g[i].emplace_back(top);
            E[top++] = {i, j, 1, 0};
            g[j].emplace_back(top);
            E[top++] = {j, i, 0, 0};
        }
    }
    int s1 = 0, s2 = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        s1 += x;
        g[0].emplace_back(top);
        E[top++] = {0, i, x, 0};
        g[i].emplace_back(top);
        E[top++] = {i, 0, 0, 0};
    }
    for (int i = n + 1; i <= n + n; ++i) {
        int x;
        cin >> x;
        s2 += x;
        g[i].emplace_back(top);
        E[top++] = {i, targ, x, 0};
        g[targ].emplace_back(top);
        E[top++] = {targ, i, 0, 0};
    }
    if (s1 != s2 || dinic() != s1) {
        cout << -1 << '\n';
        return;
    }
    for (int i = 1; i <= n; ++i) {
        for (int id : g[i]) {
            auto [_, to, cp, fl] = E[id];
            if (cp == 1 && fl == 1) {
                ans[i - 1][to - n - 1] = 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (ans[i][j] ? 'X' : '.');
        }
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