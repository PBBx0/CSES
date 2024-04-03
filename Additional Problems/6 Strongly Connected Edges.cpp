#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N];
int h[N], dp[N];
void no() {
    cout << "IMPOSSIBLE" << '\n';
    exit(0);
}
vector<pair<int, int>> ed;
void dfs(int v, int par) {
    dp[v] = h[v];
    for (int to : g[v]) if (to != par) {
        if (h[to] < h[v])
            ed.emplace_back(v, to);
        if (h[to] == 0) {
            h[to] = h[v] + 1;
            dfs(to, v);
            dp[v] = min(dp[v], dp[to]);
            if (dp[to] > h[v]) no();
        } else {
            dp[v] = min(dp[v], h[to]);
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    h[0] = 1;
    dfs(0, 0);
    for (int v = 0; v < n; ++v) if (h[v] == 0) no();
    for (auto [a, b] : ed) {
        cout << a + 1 << ' ' << b + 1 << '\n';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}