#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N], rg[N], vts, g2[N], rg2[N];
int col[N], vtx[N], vtx2[N], indeg[N], outdeg[N];
void dfs(int v) {
    col[v] = -1;
    for (int to : g[v]) if (col[to] == -2) dfs(to);
    vts.emplace_back(v);
}
void paint_comp(int v, int c) {
    col[v] = c;
    for (int to : rg[v]) if (col[to] == -1) paint_comp(to, c);
}
vector<pair<int, int>> matching;
bool dfs2(int v, int src) {
    col[v] = -2;
    if (g2[v].empty()) {
        matching.emplace_back(v, src);
        return true;
    }
    for (int to : g2[v]) if (col[to] == -3) {
        if (dfs2(to, src)) return true;
    }
    return false;
}
void dfs3(int v) {
    col[v] = -1;
    for (int to : g2[v]) if (col[to] <= -2) dfs3(to);
    vts.emplace_back(v);
}
void paint_comp2(int v, int c) {
    col[v] = c;
    for (int to : rg2[v]) if (col[to] == -1) paint_comp2(to, c);
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        rg[b].emplace_back(a);
    }
    fill(col, col + n, -2);
    for (int v = 0; v < n; ++v) if (col[v] == -2) dfs(v);
    reverse(vts.begin(), vts.end());
    int c = 0;
    for (int v : vts) if (col[v] == - 1) paint_comp(v, c++);
    if (c == 1) {
        cout << 0 << '\n';
        return;
    }
    for (int v = 0; v < n; ++v) {
        vtx[col[v]] = v;
        for (int to : g[v]) {
            if (col[v] != col[to]) {
                g2[col[v]].emplace_back(col[to]);
                rg2[col[to]].emplace_back(col[v]);
            }
        }
    }
    vector<int> fst, snd;
    for (int v = 0; v < c; ++v) {
        if (g2[v].empty()) fst.emplace_back(v);
        if (rg2[v].empty()) snd.emplace_back(v);
    }
    cout << max(sz(fst), sz(snd)) << '\n';
    int x = vtx[fst[0]] + 1, y = vtx[snd[0]] + 1;
    fill(col, col + c, -3);
    for (int v : snd) if (col[v] == -3) {
        dfs2(v, v);
    }
    for (int i = 1; i < sz(matching); ++i) {
        int from = matching[i - 1].first;
        int to = matching[i].second;
        cout << vtx[from] + 1 << ' ' << vtx[to] + 1 << '\n';
        g2[from].emplace_back(to);
        rg2[to].emplace_back(from);
    }
    vts.clear();
    for (int v = 0; v < c; ++v) if (col[v] <= -2) dfs3(v);
    std::reverse(vts.begin(), vts.end());
    int c2 = 0;
    for (int v : vts) if (col[v] == -1) paint_comp2(v, c2++);
    for (int v = 0; v < c; ++v) {
        vtx2[col[v]] = vtx[v];
        for (int to : g2[v]) if (col[to] != col[v]) {
            indeg[col[to]]++;
            outdeg[col[v]]++;
        }
    }
    fst.clear(), snd.clear();
    for (int v = 0; v < c2; ++v) {
        if (outdeg[v] == 0) fst.emplace_back(vtx2[v] + 1);
        if (indeg[v] == 0) snd.emplace_back(vtx2[v] + 1);
    }
    while (!fst.empty() && !snd.empty()) {
        cout << fst.back() << ' ' << snd.back() << '\n';
        fst.pop_back(), snd.pop_back();
    }
    bool used[c2];
    fill(used, used + c2, false);
    for (int v : snd) {
        cout << x << ' ' << v << '\n';
    }
    for (int v : fst) {
        cout << v << ' ' << y << '\n';
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