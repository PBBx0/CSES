#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N];
ll dp[N][2];
void dfs(int v, int par) {
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
    }
    ll sum = 0;
    for (int to : g[v]) if (to != par) {
        sum += max(dp[to][0], dp[to][1]);
    }
    dp[v][0] = sum;
    for (int to : g[v]) if (to != par) {
        sum -= max(dp[to][0], dp[to][1]);
        dp[v][1] = max(dp[v][1], sum + dp[to][0] + 1);
        sum += max(dp[to][0], dp[to][1]);
    }
}
void solve() {
    int n;
    cin >> n;
    for (int i = n - 1; i > 0; --i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, -1);
    cout << max(dp[0][0], dp[0][1]) << '\n';
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