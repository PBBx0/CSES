#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 5e4;
vector<int> g[N];
bitset<N> d[N];
bool col[N];
void dfs(int v) {
    col[v] = true;
    for (int to : g[v]) {
        if (!col[to]) dfs(to);
        d[v] |= d[to];
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
    for (int i = 0; i < n; ++i) d[i].set(i);
    for (int i = 0; i < n; ++i) {
        if (!col[i]) dfs(i);
    }
    for (int i = 0; i < n; ++i) cout << d[i].count() << ' ';
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