#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N];
int col[N];
bool dfs(int v, int c) {
    col[v] = c;
    for (auto to : g[v]) {
        if (col[to] == 0) {
            if (!dfs(to, 3 - c)) return false;
        } else if (col[to] == c) {
            return false;
        }
    }
    return true;
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
    bool ok = true;
    for (int v = 0; v < n; ++v) {
        if (col[v] == 0)
            ok &= dfs(v, 1);
    }
    if (!ok) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    for (int i = 0; i < n; ++i) cout << col[i] << ' ';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}