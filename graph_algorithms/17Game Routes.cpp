#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
const ll MOD = 1e9 + 7;
ll dp[N];
bool used[N];
vector<int> g[N];
ll dfs(int v) {
    if (used[v]) return dp[v];
    used[v] = true;
    for (int to : g[v]) {
        dp[v] += dfs(to);
    }
    return dp[v] %= MOD;
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
    dp[n - 1] = 1;
    cout << dfs(0) << '\n';
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