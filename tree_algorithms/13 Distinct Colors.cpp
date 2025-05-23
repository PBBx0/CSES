#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N];
set<int> cols[N];
int ans[N];
void merge(set<int>& a, set<int>& b) {
    if (sz(a) < sz(b)) swap(a, b);
    for (int el : b) a.insert(el);
    b.clear();
}
void dfs(int v, int par) {
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
        merge(cols[v], cols[to]);
    }
    ans[v] = sz(cols[v]);
}
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        cols[i].insert(c);
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
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