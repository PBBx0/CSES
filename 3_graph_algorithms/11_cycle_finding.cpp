#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        g[a].emplace_back(b, c);
    }
    vector<ll> dst(n, 0);
    vector<int> par(n, -1);
    int last_iter = 0, last_vtx = 0;
    for (int it = 0; it <= n; ++it) {
        for (int v = 0; v < n; ++v) for (auto [to, w] : g[v]) {
            if (dst[to] > dst[v] + w) {
                dst[to] = dst[v] + w;
                par[to] = v;
                last_iter = it;
                last_vtx = v;
            }
        }
    }
    if (last_iter < n) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<bool> used(n, false);
    for (; !used[last_vtx]; last_vtx = par[last_vtx]) used[last_vtx] = true;
    vector<int> outp{last_vtx};
    for (int u = par[last_vtx]; u != last_vtx; u = par[u]) outp.emplace_back(u);
    outp.emplace_back(last_vtx);
    reverse(all(outp));
    for (int el : outp) cout << el + 1 << ' ';
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