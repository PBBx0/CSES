#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
const ll INF = 1e15;
vector<pair<int, ll>> g[N], g2[N];
ll d1[N], d2[N];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        g[a].emplace_back(b, w);
        g2[b].emplace_back(a, w);
    }
    fill(d1, d1 + n, INF);
    fill(d2, d2 + n, INF);
    d1[0] = d2[n - 1] = 0;
    set<pair<ll, int>> s;
    for (int v = 0; v < n; ++v) {
        s.insert(make_pair(d1[v], v));
    }
    while (!s.empty()) {
        auto [d, v] = *s.begin();
        s.erase(s.begin());
        for (auto [to, w] : g[v]) {
            if (d1[to] > d + w) {
                ll& x = d1[to];
                s.erase(make_pair(x, to));
                x = d + w;
                s.insert(make_pair(x, to));
            }
        }
    }
    for (int v = 0; v < n; ++v) {
        s.insert(make_pair(d2[v], v));
    }
    while (!s.empty()) {
        auto [d, v] = *s.begin();
        s.erase(s.begin());
        for (auto [to, w] : g2[v]) {
            if (d2[to] > d + w) {
                ll&x = d2[to];
                s.erase(make_pair(x, to));
                x = d + w;
                s.insert(make_pair(x, to));
            }
        }
    }
    ll res = INF;
    for (int v = 0; v < n; ++v) {
        for (auto [to, w] : g[v]) {
            res = min(res, d1[v] + w / 2 + d2[to]);
        }
    }
    cout << res << '\n';
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