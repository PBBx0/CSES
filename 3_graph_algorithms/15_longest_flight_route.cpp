#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

vector<vector<int>> g;
vector<int> dp, nxt;

int dfs(int v) {
    if (dp[v] != -2) return dp[v];
    dp[v] = -1;
    for (int to : g[v]) {
        int r = dfs(to);
        if (r > dp[v]) {
            dp[v] = r;
            nxt[v] = to;
        }
    }
    if (dp[v] >= 0) dp[v] += 1;
    return dp[v];
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    dp.resize(n, -2);
    nxt.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
    }
    dp[n - 1] = 0;
    int r = dfs(0);
    if (r == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << r + 1 << '\n';
        for (int u = 0; u != -1; u = nxt[u]) cout << u + 1 << ' ';
        cout << '\n';
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