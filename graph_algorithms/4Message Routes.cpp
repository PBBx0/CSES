#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5 + 1, INF = 1e9 + 7;
vector<int> g[N];
int dist[N], par[N];
void solve() {
    fill(par, par + N, -1);
    fill(dist, dist + N, INF);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dist[0] = 0;
    deque<int> dq{0};
    while (!dq.empty()) {
        int v = dq.front();
        dq.pop_front();
        for (auto to : g[v]) if (dist[to] == INF) {
            dist[to] = dist[v] + 1;
            par[to] = v;
            dq.emplace_back(to);
        }
    }
    if (dist[n - 1] == INF) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    vector<int> out;
    for (int v = n - 1; v != -1; v = par[v]) {
        out.emplace_back(v);
    }
    reverse(out.begin(), out.end());
    cout << sz(out) << '\n';
    for (int v : out) cout << v + 1 << ' ';
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