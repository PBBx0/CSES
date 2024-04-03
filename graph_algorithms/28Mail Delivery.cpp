#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
set<int> g[N];
vector<int> vts;
void euler_path(int v) {
    while (!g[v].empty()) {
        int to = *g[v].begin();
        g[v].erase(to);
        g[to].erase(v);
        euler_path(to);
        vts.emplace_back(to);
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].insert(b);
        g[b].insert(a);
    }
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) & 1) {
            cout << "IMPOSSIBLE" << '\n';
            return;
        }
    }
    euler_path(0);
    if (sz(vts) != m) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    vts.emplace_back(0);
    for (auto el : vts) cout << el + 1 << ' ';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}