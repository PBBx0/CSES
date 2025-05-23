#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N];
int dp[N][2], ans[N];
int dfs(int v, int par) {
    for (int to : g[v]) if (to != par) {
        int x = dfs(to, v) + 1;
        if (x > dp[v][0]) {
            dp[v][1] = dp[v][0];
            dp[v][0] = x;
        } else if (x > dp[v][1]) {
            dp[v][1] = x;
        }
    }
    return dp[v][0];
}
void dfs2(int v, int par, int top) {
    ans[v] = max(top, dp[v][0]);
    for (int to : g[v]) if (to != par) {
        if (dp[to][0] + 1 == dp[v][0]) {
            dfs2(to, v, max(top, dp[v][1]) + 1);
        } else {
            dfs2(to, v, max(top, dp[v][0]) + 1);
        }
    }
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, -1);
    dfs2(0, -1, 0);
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
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