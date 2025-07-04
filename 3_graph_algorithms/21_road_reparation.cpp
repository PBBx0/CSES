#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

struct DSU {
    vector<int> dsu;

    DSU(int n) : dsu(n, -1) {}

    int get(int v) {
        return dsu[v] < 0 ? v : dsu[v] = get(dsu[v]);
    }

    int comp_size(int v) {
        return -dsu[get(v)];
    }

    bool unite(int u, int v) {
        u = get(u), v = get(v);
        if (u == v) return false;
        if (dsu[u] > dsu[v]) swap(u, v);
        return dsu[u] += dsu[v], dsu[v] = u, true;
    }

};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    for (auto& [c, a, b] : edges) {
        cin >> a >> b >> c;
        --a, --b;
    }
    sort(all(edges));
    ll ans = 0;
    int cnt = 0;
    DSU dsu(n);
    for (auto [c, a, b] : edges) {
        if (dsu.unite(a, b)) {
            ans += c, cnt += 1;
        }
    }
    if (cnt == n - 1) {
        cout << ans << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}
