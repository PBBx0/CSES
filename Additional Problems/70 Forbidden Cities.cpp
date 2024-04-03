#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5, INF = 1e9 + 1000 - 7;
vector<int> g[N];
vector<pair<int, int>> sectors[N];
int h[N], dp[N], col[N], comp[N];
void dfs(int v) {
    col[v] = 1;
    dp[v] = h[v];
    for (int to : g[v]) {
        if (col[to] == 1) {
            dp[v] = min(dp[v], h[to]);
        } else {
            h[to] = h[v] + 1;
            dfs(to);
            dp[v] = min(dp[v], dp[to]);
        }
    }
}
int max_c = 0;
void paint_comp(int v, int c) {
    comp[v] = c;
    col[v] = 2;
    for (int to : g[v]) {
        if (col[to] == 1) {
            if (dp[to] >= h[v]) {
                int l = ++max_c;
                paint_comp(to, max_c);
                sectors[v].emplace_back(l, max_c);
            } else {
                paint_comp(to, c);
            }
        }
    }
}
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    fill(col, col + n, -1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0);
    paint_comp(0, 0);
    auto get_iter = [&](int v, int x) {
        if (sectors[v].empty() || sectors[v].back().second < x || sectors[v][0].first > x)
            return sectors[v].end();
        auto it = --upper_bound(sectors[v].begin(), sectors[v].end(), make_pair(x, INF));
        return it->second < x ? sectors[v].end() : it;
    };
    for (int i = 0; i < q; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--, c--;
        bool ok = get_iter(c, comp[a]) == get_iter(c, comp[b]);
        if (a == c || b == c) ok = false;
        cout << (ok ? "YES" : "NO") << '\n';
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