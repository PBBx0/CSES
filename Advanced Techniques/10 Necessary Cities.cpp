#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N];
int dp[N], h[N], col[N];
set<int> art_pts;
void dfs(int v) {
    int cnt_ch = 0;
    dp[v] = h[v];
    col[v] = 1;
    for (int to : g[v]) {
        if (col[to] == 0) {
            h[to] = h[v] + 1;
            dfs(to);
            if (v != 0 && dp[to] >= h[v]) art_pts.insert(v);
            dp[v] = min(dp[v], dp[to]);
            cnt_ch++;
        } else {
            dp[v] = min(dp[v], h[to]);
        }
    }
    if (v == 0 && cnt_ch > 1) art_pts.insert(v);
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
    dfs(0);
    cout << sz(art_pts) << '\n';
    for (int v : art_pts) cout << v + 1 << ' ';
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