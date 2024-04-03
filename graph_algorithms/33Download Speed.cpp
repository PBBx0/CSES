#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct edge {
    int from, to, cap, flow = 0;
    edge(int a = 0, int b = 0, int cap = 0) : from(a), to(b), cap(cap) {}
};
const int M = 2000, N = 500, INF = 1e9 + 7;
edge E[M];
vector<int> g[N];
int n;
int dist[N], par[N];
int bfs(int v0 = 0, int cc = 1) {
    fill(dist, dist + n, -1);
    dist[v0] = 0;
    vector<int> q{v0};
    for (int st = 0; st < sz(q); ++st) {
        int v = q[st];
        for (int id : g[v]) {
            auto [_, to, cp, f] = E[id];
            if (cp - f >= cc && dist[to] == -1) {
                dist[to] = dist[v] + 1;
                par[to] = id;
                q.emplace_back(to);
            }
        }
    }
    if (dist[n - 1] == -1) return 0;
    int min_c = INF;
    for (int v = n - 1; v != v0; ) {
        auto [from, _, cp, f] = E[par[v]];
        min_c = min(min_c, cp - f);
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
void solve() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        E[2 * i] = edge(a, b, c);
        E[2 * i + 1] = edge(b, a, 0);
        g[a].emplace_back(2 * i);
        g[b].emplace_back(2 * i + 1);
    }
    ll flow = 0;
    for (int c = INF; c > 0; c >>= 1) {
        while (int pushed = bfs(0, c)) {
            flow += pushed;
        }
    }
    cout << flow << '\n';
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