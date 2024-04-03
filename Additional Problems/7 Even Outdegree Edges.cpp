#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
const int N = 1e5, M = 2e5;
pair<int, int> E[M];
int xe[M];
bool rev[M];
vector<int> g[N];
int col[N], sz[N], comp_e[N], d[N];
int n, m;
void paint_comp(int v, int c) {
    col[v] = c;
    for (int i : g[v]) {
        int to = v ^ xe[i];
        comp_e[c]++;
        if (col[to] != c) paint_comp(to, c);
    }
}
bool fix(int v) {
    col[v] = 1;
    bool f = false;
    for (int i : g[v]) {
        int to = v ^ xe[i];
        if (col[to]) continue;
        bool t = sz[to] ^ fix(to);
        if (t) rev[i] ^= true;
        f ^= t;
    }
    return f;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        E[i] = {a, b};
        xe[i] = a ^ b;
        rev[i] = false;
        g[a].emplace_back(i);
        g[b].emplace_back(i);
        sz[a] ^= 1;
    }
    int c = 0;
    for (int v = 0; v < n; ++v) if (!col[v]) paint_comp(v, ++c);
    for (int i = 1; i <= c; ++i) {
        comp_e[i] >>= 1;
        if (comp_e[i] & 1) {
            cout << "IMPOSSIBLE" << '\n';
            return;
        }
    }
    fill(col, col + n, 0);
    for (int v = 0; v < n; ++v) {
        if (!col[v]) fix(v);
        sz[v] = 0;
    }
    for (int i = 0; i < m; ++i) {
        auto [a, b] = E[i];
        if (rev[i]) swap(a, b);
        sz[a]++;
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
    for (int i = 0; i < n; ++i)
        assert(sz[i] % 2 == 0);
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    auto start = clock();
    solve();
    cerr << (clock() - start) * 1e3 / CLOCKS_PER_SEC << '\n';
    return 0;
}