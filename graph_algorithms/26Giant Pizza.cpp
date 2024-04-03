#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N], rg[N], vts;
int col[N];
void dfs(int v) {
    col[v] = 0;
    for (int to : g[v]) if (col[to] == -1) {
        dfs(to);
    }
    vts.emplace_back(v);
}
void paint_comp(int v, int c) {
    col[v] = c;
    for (int to : rg[v]) if (col[to] == 0) {
        paint_comp(to, c);
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    fill(col, col + 2 * m, -1);
    for (int i = 0; i < n; ++i) {
        char t1, t2;
        int x1, x2;
        cin >> t1 >> x1 >> t2 >> x2;
        x1--, x2--;
        x1 = t1 == '-' ? x1 + m : x1;
        x2 = t2 == '-' ? x2 + m : x2;
        int mx1 = x1 >= m ? x1 - m : x1 + m;
        int mx2 = x2 >= m ? x2 - m : x2 + m;
        g[mx1].emplace_back(x2);
        rg[x2].emplace_back(mx1);
        g[mx2].emplace_back(x1);
        rg[x1].emplace_back(mx2);
    }
    for (int v = 0; v < 2 * m; ++v) if (col[v] == -1) {
        dfs(v);
    }
    std::reverse(vts.begin(), vts.end());
    int c = 0;
    for (int v : vts) if (col[v] == 0) {
        paint_comp(v, ++c);
    }
    vector<bool> ans(m);
    for (int v = 0; v < m; ++v) {
        if (col[v] == col[v + m]) {
            cout << "IMPOSSIBLE" << '\n';
            return;
        }
        ans[v] = col[v] > col[v + m];
    }
    for (bool el : ans) cout << (el ? '+' : '-') << ' ';
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