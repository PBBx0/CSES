#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N];
int col[N];
int dfs(int v) {
    col[v] = 1;
    int res = 1;
    for (int to : g[v]) if (!col[to]) {
        res += dfs(to);
    }
    return res;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    vector<int> a;
    for (int v = 0; v < n; ++v) {
        if (!col[v]) a.emplace_back(dfs(v));
    }
    bitset<N + 1> b;
    b.set(0);
    for (int x : a) {
        b |= (b << x);
    }
    for (int i = 1; i <= n; ++i) cout << b[i];
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