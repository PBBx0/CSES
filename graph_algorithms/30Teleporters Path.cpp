#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
int deg[N], ptr[N];
vector<int> g[N], vts;
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        deg[a]++;
        deg[b]--;
    }
    bool ok = (deg[0] == 1 && deg[n - 1] == -1);
    for (int v = 1; v < n - 1; ++v) ok &= deg[v] == 0;
    if (!ok) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    vector<int> st{0};
    while (!st.empty()) {
        int v = st.back();
        if (ptr[v] == sz(g[v])) {
            vts.emplace_back(v);
            st.pop_back();
        } else {
            st.emplace_back(g[v][ptr[v]++]);
        }
    }
    if (sz(vts) != m + 1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    std::reverse(vts.begin(), vts.end());
    for (int el : vts) cout << el + 1 << ' ';
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