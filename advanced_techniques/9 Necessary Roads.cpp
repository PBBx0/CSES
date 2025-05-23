#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N];
int dp[N], h[N], col[N];
vector<pair<int, int>> brs;
void dfs(int v, int par) {
    col[v] = 1;
    dp[v] = h[v];
    for (int to : g[v]) if (to != par) {
        if (col[to] == 0) {
            h[to] = h[v] + 1;
            dfs(to, v);
            if (dp[to] > h[v]) brs.emplace_back(v, to);
            dp[v] = min(dp[v], dp[to]);
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
    dfs(0, 0);
    cout << sz(brs) << '\n';
    for (auto [a, b] : brs) cout << a + 1 << ' ' << b + 1 << '\n';
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