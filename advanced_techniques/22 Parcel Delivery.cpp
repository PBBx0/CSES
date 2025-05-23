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
const int N = 500, M = 1000, INF = 1e9 + 7;
edge E[2 * M];
vector<int> g[N];
int d[N], curr[N], par[N];
int n, m, k;
int flow_like_a_river() {
    int res = 0;
    while (k > 0) {
        fill(par, par + n, -1);
        fill(curr, curr + n, 0);
        fill(d, d + n, INF);
        curr[0] = INF;
        d[0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int id = 0; id < 2 * m; ++id) {
                auto [from, to, cap, cost, fl] = E[id];
                if (cap - fl == 0) continue;
                if (d[to] > d[from] + cost) {
                    d[to] = d[from] + cost;
                    par[to] = id;
                    curr[to] = min(curr[from], cap - fl);
                }
            }
        }
        int pushed = curr[n - 1];
        if (!pushed) return -1;
        pushed = min(pushed, k);
        k -= pushed;
        res += pushed * d[n - 1];
        for (int v = n - 1; par[v] != -1; ) {
            int id = par[v];
            E[id].flow += pushed;
            E[id ^ 1].flow -= pushed;
            v = E[id].from;
        }
    }
    return res;
}
void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int a, b, cp, cs;
        cin >> a >> b >> cp >> cs;
        a--, b--;
        E[2 * i] = {a, b, cp, cs};
        E[2 * i + 1] = {b, a, 0, -cs};
        g[a].emplace_back(2 * i);
        g[b].emplace_back(2 * i + 1);
    }
    cout << flow_like_a_river() << '\n';
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