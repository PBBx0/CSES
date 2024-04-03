#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N], order;
int up[N], tin[N], tout[N], sz[N], val[N], h[N], par[N];

int calc_sz(int v) {
    sz[v] = 1;
    for (int& to : g[v]) if (to != par[v]) {
        h[to] = h[v] + 1;
        par[to] = v;
        sz[v] += calc_sz(to);
        if (sz[to] > sz[g[v][0]]) {
            swap(to, g[v][0]);
        }
    }
    return sz[v];
}
void dfs_hld(int v) {
    tin[v] = sz(order);
    order.emplace_back(val[v]);
    for (int to : g[v]) if (to != par[v]) {
        if (to == g[v][0]) {
            up[to] = up[v];
        } else {
            up[to] = to;
        }
        dfs_hld(to);
    }
    tout[v] = sz(order);
}
struct ST {
    int N = 1;
    vector<int> t;
    void build(vector<int>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) t[i + N] = a[i];
        for (int i = N - 1; i > 0; --i) t[i] = max(t[i + i], t[i + i +1]);
    }
    int get(int l, int r) {
        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }
    void set(int p, int x) {
        for (t[p += N] = x; p > 1; p >>= 1) {
            t[p >> 1] = max(t[p], t[p ^ 1]);
        }
    }
};
ST seg_tree;
int get_max(int a, int b) {
    int res = 0;
    while (up[a] != up[b]) {
        if (h[up[a]] < h[up[b]]) swap(a, b);
        res = max(res, seg_tree.get(tin[up[a]], tin[a] + 1));
        a = par[up[a]];
    }
    if (h[a] > h[b]) swap(a, b);
    res = max(res, seg_tree.get(tin[a], tin[b] + 1));
    return res;
}
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> val[i];
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    calc_sz(0);
    dfs_hld(0);
    seg_tree.build(order);
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            seg_tree.set(tin[s], x);
        } else {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << get_max(a, b) << ' ';
        }
    }
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