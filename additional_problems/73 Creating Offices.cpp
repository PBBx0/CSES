#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5, LOG = 18, INF = 1e9 + 1000 - 7;
int d;
vector<int> g[N], vts;
int h[N], near[N], sz[N], level[N], up[LOG][N], dist[LOG][N];
set<pair<int, int>> s;
void dfs(int v, int p) {
    s.emplace(h[v], v);
    for (int to : g[v]) if (to != p) {
        h[to] = h[v] + 1;
        dfs(to, v);
    }
}
int calc_sz(int v, int p) {
    sz[v] = 1;
    for (int to : g[v]) if (to != p && level[to] == -1) sz[v] += calc_sz(to, v);
    vts.emplace_back(v);
    return sz[v];
}
void dfs2(int v, int p, int ctr, int lvl, int cur_d) {
    up[lvl][v] = ctr;
    dist[lvl][v] = cur_d;
    for (int to : g[v]) if (to != p && level[to] == -1) {
        dfs2(to, v, ctr, lvl, cur_d + 1);
    }
}
void find_centroid(int v, int lvl) {
    vts.clear();
    int all_sz = calc_sz(v, v);
    for (int x : vts) {
        if (sz[x] * 2 >= all_sz) {
            v = x;
            break;
        }
    }
    level[v] = lvl;
    dfs2(v, v, v, lvl, 0);
    for (int to : g[v]) if (level[to] == -1) find_centroid(to, lvl + 1);
}
void update(int v) {
    for (int l = level[v]; l >= 0; --l) {
        int c = up[l][v], dd = dist[l][v];
        near[c] = min(near[c], dd);
    }
}
int get(int v) {
    int res = INF;
    for (int l = level[v]; l >= 0; --l) {
        int c = up[l][v], dd = dist[l][v];
        res = min(res, dd + near[c]);
    }
    return res;
}
void solve() {
    int n;
    cin >> n >> d;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
    fill(level, level + n, -1);
    fill(near, near + n, INF);
    find_centroid(0, 0);
    vector<int> ans;
    while (!s.empty()) {
        auto [_, v] = *s.rbegin();
        s.erase(--s.end());
        if (get(v) >= d) {
            ans.emplace_back(v);
            update(v);
        }
    }
    cout << sz(ans) << '\n';
    for (int v : ans) cout << v + 1 << ' ';
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
    solve();
    return 0;
}