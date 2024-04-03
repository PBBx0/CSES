#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5 + 2;
vector<int> g[N];
int col[N];
void dfs(int v, int c) {
    col[v] = c;
    for (int to : g[v]) if (col[to] == 0) {
        dfs(to, c);
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
        g[b].emplace_back(a);
    }
    vector<int> vts;
    int c = 0;
    for (int i = 0; i < n; ++i) {
        if (col[i] == 0) {
            dfs(i, ++c);
            vts.emplace_back(i);
        }
    }
    cout << sz(vts) - 1 << '\n';
    for (int i = 1; i < sz(vts); ++i) {
        cout << vts[i - 1] + 1 << ' ' << vts[i] + 1 << '\n';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}