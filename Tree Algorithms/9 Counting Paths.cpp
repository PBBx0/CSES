#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5, LOG = 18;
vector<int> g[N];
int up[LOG][N], h[N], d[N], ans[N];

void dfs(int v, int par) {
    up[0][v] = par;
    for (int to : g[v]) if (to != par) {
        h[to] = h[v] + 1;
        dfs(to, v);
    }
}

int get(int v, int k) {
    for (int i = 0; i < LOG; ++i) {
        if (k & (1 << i)) v = up[i][v];
    }
    return v;
}
int lca(int a, int b) {
    if (h[a] > h[b]) swap(a, b);
    b = get(b, h[b] - h[a]);
    if (a == b) return a;
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[i][a] != up[i][b]) {
            a = up[i][a], b = up[i][b];
        }
    }
    return up[0][a];
}
int calc(int v, int par) {
    int res = 0;
    for (int to : g[v]) if (to != par) {
        res += calc(to, v);
    }
    ans[v] += res + d[v];
    return res + d[v];
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
    for (int i = 1; i < LOG; ++i) {
        for (int v = 0; v < n; ++v) {
            up[i][v] = up[i - 1][up[i - 1][v]];
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        d[a]++, d[b]++;
        int l = lca(a, b);
        d[l] -= 2;
        ans[l]++;
    }
    calc(0, 0);
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