#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> order, g[N];
int col[N];
bool ok = true;
void dfs(int v) {
    col[v] = 1;
    for (auto to : g[v]) {
        if (col[to] == 1) ok = false;
        if (col[to] == 0) dfs(to);
    }
    col[v] = 2;
    order.emplace_back(v);
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
    }
    for (int v = 0; v < n; ++v) if (col[v] == 0) {
        dfs(v);
    }
    if (!ok) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    reverse(order.begin(), order.end());
    for (auto el : order) cout << el + 1 << ' ';
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