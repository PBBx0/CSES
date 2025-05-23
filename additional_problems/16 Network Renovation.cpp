#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N], leafs[N], vts;
int cnt[N];
void merge(vector<int> & a, vector<int> & b) {
    if (sz(a) < sz(b)) swap(a, b);
    for (int el : b) a.emplace_back(el);
    b.clear();
}
void dfs(int v, int par) {
    if (v != par && sz(g[v]) == 1) leafs[v].emplace_back(v);
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
        merge(leafs[v], leafs[to]);
    }
}
int calc_cnt_leafs(int v, int par) {
    cnt[v] = (sz(g[v]) == 1 && v != par);
    for (int to : g[v]) if (to != par) {
        cnt[v] += calc_cnt_leafs(to, v);
    }
    vts.emplace_back(v);
    return cnt[v];
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    int leafs_all = calc_cnt_leafs(0, 0);
    int v = 0;
    for (int x : vts) {
        if (cnt[x] * 2 >= leafs_all) {
            v = x;
            break;
        }
    }
    for (int to : g[v]) {
        dfs(to, v);
    }
    vector<vector<int>> t(sz(g[v]));
    set<pair<int, int>> s;
    for (int i = 0; i < sz(g[v]); ++i) {
        swap(t[i], leafs[g[v][i]]);
        s.emplace(sz(t[i]), i);
    }
    vector<pair<int, int>> ans;
    while (sz(s) >= 2) {
        auto [c1, i1] = *s.rbegin();
        s.erase(--s.end());
        auto [c2, i2] = *s.rbegin();
        s.erase(--s.end());
        ans.emplace_back(t[i1].back(), t[i2].back());
        t[i1].pop_back(), t[i2].pop_back();
        c1--, c2--;
        if (c1) s.emplace(c1, i1);
        if (c2) s.emplace(c2, i2);
    }
    if (!s.empty()) {
        auto [c, i] = *s.rbegin();
        assert(c == 1);
        ans.emplace_back(v, t[i].back());
        t[i].pop_back();
    }
    cout << sz(ans) << '\n';
    for (auto [a, b] : ans) cout << a + 1 << ' ' << b + 1 << '\n';
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