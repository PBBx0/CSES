#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e15;
const int N = 1e5, MOD = 1e9 + 7;
vector<pair<int, ll>> g[N];
ll dist[N], cnt[N], mi[N], ma[N];
set<pair<ll, int>> s;
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g[a].emplace_back(b, c);
    }
    fill(dist, dist + n, INF);
    fill(mi, mi + n, MOD);
    cnt[0] = 1;
    dist[0] = 0;
    mi[0] = 0;
    for (int v = 0; v < n; ++v) s.emplace(dist[v], v);
    while (!s.empty()) {
        auto [d, v] = *s.begin();
        s.erase(s.begin());
        for (auto [to, w] : g[v]) {
            if (dist[to] == d + w) {
                cnt[to] = (cnt[to] + cnt[v]) % MOD;
                mi[to] = min(mi[to], mi[v] + 1);
                ma[to] = max(ma[to], ma[v] + 1);
            } else if (dist[to] > d + w) {
                cnt[to] = cnt[v];
                mi[to] = mi[v] + 1;
                ma[to] = ma[v] + 1;
                ll& x = dist[to];
                s.erase(make_pair(x, to));
                x = d + w;
                s.emplace(x, to);
            }
        }
    }
    cout << dist[n - 1] << ' ' << cnt[n - 1] << ' ' << mi[n - 1] << ' ' << ma[n - 1] << '\n';
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