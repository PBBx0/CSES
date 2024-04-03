#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N], rg[N], bucket[N];
int sdom[N], dom[N], par[N], dsu[N], tin[N], nit[N], t = 0, label[N];
int find(int v, bool flag = false) {
    if (v == dsu[v]) return flag ? -1 : v;
    int p = find(dsu[v], true);
    if (p < 0) return v;
    if (sdom[label[dsu[v]]] < sdom[label[v]]) label[v] = label[dsu[v]];
    dsu[v] = p;
    return flag ? p : label[v];
}
void unite(int a, int b) {
    dsu[b] = a;
}
void dfs(int v) {
    nit[t] = v;
    tin[v] = label[t] = sdom[t] = dsu[t] = t;
    t++;
    for (int to : g[v]) {
        if (tin[to] == -1) dfs(to), par[tin[to]] = tin[v];
        rg[tin[to]].emplace_back(tin[v]);
    }
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
    fill(tin, tin + n, -1);
    dfs(0);
    for (int v = n - 1; v >= 0; --v) {
        for (int to : rg[v]) {
            sdom[v] = min(sdom[v], sdom[find(to)]);
        }
        if (v) bucket[sdom[v]].emplace_back(v);
        for (int to : bucket[v]) {
            int p = find(to);
            if (sdom[p] == sdom[to]) dom[to] = sdom[to];
            else dom[to] = p;
        }
        if (v) unite(par[v], v);
    }
    for (int i = 1; i < n; ++i) {
        if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    }
    set<int> ans{0};
    for (int v = n - 1; v != 0; ) {
        ans.insert(v);
        v = nit[dom[tin[v]]];
    }
    cout << sz(ans) << '\n';
    for (int v : ans) cout << v + 1 << ' ';
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