#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
vector<array<int, 2>> g;
vector<bool> used;
string out;
void dfs(int v) {
    used[v] = true;
    if (!used[g[v][1]]) {
        out += '1';
        dfs(g[v][1]);
    } else if (!used[g[v][0]]) {
        out += '0';
        dfs(g[v][0]);
    }
}
void solve() {
    int n;
    cin >> n;
    int m = 1 << n;
    g.resize(m);
    used.resize(m);
    for (int mask = 0; mask < m; ++mask) {
        int nx = mask << 1;
        if (nx >= m) nx -= m;
        g[mask][0] = nx;
        g[mask][1] = nx + 1;
    }
    out = string(n, '0');
    dfs(0);
    cout << out << '\n';
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