#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5, LOG = 18;
vector<int> g[N];
int h[N], up[LOG][N];
void calc_h(int v, int par) {
    up[0][v] = par;
    for (int to : g[v]) if (to != par) {
        h[to] = h[v] + 1;
        calc_h(to, v);
    }
}
int getk(int v, int k) {
    for (int i = 0; i < LOG; ++i) {
        if (k & (1 << i)) v = up[i][v];
    }
    return v;
}
int get_lca(int a, int b) {
    if (h[a] > h[b]) swap(a, b);
    b = getk(b, h[b] - h[a]);
    if (a == b) return a;
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[i][a] != up[i][b]) {
            a = up[i][a], b = up[i][b];
        }
    }
    return up[0][a];
}
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    calc_h(0, -1);
    for (int i = 1; i < LOG; ++i) {
        for (int v = 0; v < n; ++v) {
            up[i][v] = up[i - 1][up[i - 1][v]];
        }
    }
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << h[a] + h[b] - 2 * h[get_lca(a, b)] << '\n';
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