#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5, INF = 1e9 + 7;
vector<int> g[N];
int dp[N], nx[N];
int dfs(int v) {
    if (dp[v] != -1) return dp[v];
    dp[v] = -INF;
    for (auto to : g[v]) {
        int x = dfs(to);
        if (x + 1 > dp[v]) {
            dp[v] = x + 1, nx[v] = to;
        }
    }
    return dp[v];
}
void solve() {
    int n, m;
    cin >> n >> m;
    fill(dp, dp + n, -1);
    fill(nx, nx + n, -1);
    dp[n - 1] = 1;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
    }
    dfs(0);
    if (dp[0] <= 0) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    vector<int> out;
    for (int v = 0; v != n - 1; v = nx[v]) {
        out.emplace_back(v);
    }
    out.emplace_back(n - 1);
    cout << sz(out) << '\n';
    for (int el : out) cout << el + 1 << ' ';
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