#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 100;
vector<int> g[N], g2[N + N];
int mt[N], col[N], paired[N + N], visited[N + N];
bool kuhn(int v, int c) {
    if (col[v] == c) return false;
    col[v] = c;
    for (int to : g[v]) {
        if (mt[to] == -1) {
            return mt[to] = v, true;
        }
    }
    for (int to : g[v]) {
        if (kuhn(mt[to], c)) {
            return mt[to] = v, true;
        }
    }
    return false;
}
void dfs(int v) {
    visited[v] = 1;
    for (int to : g2[v]) if (!visited[to]) dfs(to);
}
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char t;
            cin >> t;
            if (t != '.') {
                g[i].emplace_back(j);
            }
        }
    }
    fill(mt, mt + n, -1);
    int res = 0;
    for (int v = 0; v < n; ++v) res += kuhn(v, v + 1);
    fill(paired, paired + n + n, -1);
    for (int v = 0; v < n; ++v) if (mt[v] != -1) {
        paired[mt[v]] = v + n;
        paired[v + n] = mt[v];
        g2[v + n].emplace_back(mt[v]);
    }
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) if (to + n != paired[v]) {
            g2[v].emplace_back(to + n);
        }
    }
    for (int v = 0; v < n; ++v) {
        if (!visited[v] && paired[v] == -1) dfs(v);
    }
    cout << res << '\n';
    for (int v = 0; v < n; ++v) {
        if (!visited[v]) cout << 1 << ' ' << v + 1 << '\n';
        if (visited[v + n]) cout << 2 << ' ' << v + 1 << '\n';
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