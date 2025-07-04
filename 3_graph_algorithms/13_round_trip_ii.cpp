#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

vector<vector<int>> g;

vector<int> col, st;

void dfs(int v) {
    col[v] = 1;
    st.emplace_back(v);
    for (int to : g[v]) {
        if (col[to] == 2) continue;
        if (col[to] == 0) {
            dfs(to);
            continue;
        }
        vector<int> outp{to};
        while (st.back() != to) {
            outp.emplace_back(st.back());
            st.pop_back();
        }
        outp.emplace_back(to);
        reverse(all(outp));
        cout << sz(outp) << '\n';
        for (int el : outp) cout << el + 1 << ' ';
        cout << '\n';
        exit(EXIT_SUCCESS);
    }
    st.pop_back();
    col[v] = 2;
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n), col.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
    }
    for (int i = 0; i < n; ++i) {
        if (col[i] == 0) dfs(i);
    }
    cout << "IMPOSSIBLE\n";
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