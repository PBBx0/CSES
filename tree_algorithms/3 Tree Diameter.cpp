#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N];
int dp[N], ans = 0;
void dfs(int v, int par) {
    int res = 0;
    int mx = -1;
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
        res = max(res, 2 + mx + dp[to]);
        mx = max(mx, dp[to]);
    }
    dp[v] = mx + 1;
    ans = max(ans, res);
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
    cout << ans << '\n';
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