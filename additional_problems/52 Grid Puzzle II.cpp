#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct edge {
    int from, to, cap, cost, flow;
    edge(int from = 0, int to = 0, int cp = 0, int cs = 0, int fl = 0) :\
    from(from), to(to), cap(cp), cost(cs), flow(fl) {}
};
const int N = 50, N2 = 102, M = 5100, INF = 1e9 + 1000 - 7;
edge E[M];
vector<int> g[N2];
int d[N2], col[N2], p[N2], par[N2];
int ans[N][N];
void solve() {
    int top = 0;
    int n;
    cin >> n;
    int start = 0, targ = n + n + 1, s = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        s += x;
        g[start].emplace_back(top);
        E[top++] = {start, i, x, 0, 0};
        g[i].emplace_back(top);
        E[top++] = {i, start, 0, 0, 0};
    }
    for (int i = n + 1; i <= n + n; ++i) {
        int x;
        cin >> x;
        g[i].emplace_back(top);
        E[top++] = {i, targ, x, 0, 0};
        g[targ].emplace_back(top);
        E[top++] = {targ, i, 0, 0, 0};
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = n + 1; j <= n + n; ++j) {
            int x;
            cin >> x;
            x = 1000 - x;
            g[i].emplace_back(top);
            E[top++] = {i, j, 1, x, 0};
            g[j].emplace_back(top);
            E[top++] = {j, i, 0, -x, 0};
        }
    }
    int flow = 0, cost = s * 1000;
    int n2 = 1 + n + n + 1;
    fill(d, d + n2, INF);
    fill(par, par + n2, -1);
    d[start] = 0;
    for (int i = 0; i < n2; ++i) {
        for (int id = 0; id < top; ++id) {
            auto [from, to, cp, cs, fl] = E[id];
            if (cp - fl == 0) continue;
            if (d[to] > d[from] + cs) {
                d[to] = d[from] + cs;
                par[to] = id;
            }
        }
    }
    int cur_col = 1;
    while (d[targ] != INF) {
        for (int i = 0; i < n2; ++i) p[i] += d[i];
        int pushed = INF, cur_cost = 0;
        for (int v = targ; par[v] != -1; ) {
            auto [from, _, cp, cs, fl] = E[par[v]];
            pushed = min(pushed, cp - fl);
            cur_cost += cs;
            v = from;
        }
        flow += pushed;
        cost -= pushed * cur_cost;
        for (int v = targ; par[v] != -1; ) {
            E[par[v]].flow += pushed;
            E[par[v] ^ 1].flow -= pushed;
            v = E[par[v]].from;
        }
        fill(d, d + n2, INF);
        d[0] = 0;
        for (int i = 0; i < n2; ++i) {
            int nv = -1;
            for (int v = 0; v < n2; ++v) if (col[v] != cur_col) {
                if (nv == -1 || d[v] < d[nv]) nv = v;
            }
            if (nv == -1 || d[nv] == INF) break;
            col[nv] = cur_col;
            for (int id : g[nv]) {
                auto [_, to, cp, cs, fl] = E[id];
                if (cp - fl == 0 || col[to] == cur_col) continue;
                if (d[to] > d[nv] + p[nv] + cs - p[to]) {
                    d[to] = d[nv] + p[nv] + cs - p[to];
                    par[to] = id;
                }
            }
        }
        cur_col++;
    }
    if (flow != s) {
        cout << -1 << '\n';
        return;
    }
    for (int i = 1; i <= n; ++i) {
        for (int id : g[i]) {
            auto [_, to, cp, cs, fl] = E[id];
            if (cp == 1 && fl == 1) {
                ans[i - 1][to - n - 1] = 1;
            }
        }
    }
    cout << cost << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << (ans[i][j] ? 'X' : '.');
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