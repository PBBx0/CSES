#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll N = 1e5, INF = 1e15;
vector<pair<int, ll>> g[N];
ll dist[N];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        g[a].emplace_back(b, w);
    }
    fill(dist, dist + n, INF);
    dist[0] = 0;
    set<pair<ll, int>> s;
    for (int v = 0; v < n; ++v) {
        s.insert(make_pair(dist[v], v));
    }
    while (!s.empty()) {
        auto [d, v] = *s.begin();
        s.erase(s.begin());
        for (auto [to, w] : g[v]) {
            if (dist[to] > d + w) {
                ll& x = dist[to];
                s.erase(make_pair(x, to));
                x = d + w;
                s.insert(make_pair(x, to));
            }
        }
    }
    for (int v = 0; v < n; ++v) cout << dist[v] << ' ';
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