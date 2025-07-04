#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
    }
    vector<bool> used(m, false);
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) & 1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    vector<int> st, ans;
    vector<int> ptr(n);
    st.emplace_back(0);
    while (!st.empty()) {
        int v = st.back();
        while (ptr[v] < sz(g[v]) && used[g[v][ptr[v]].second]) {
            ++ptr[v];
        }
        if (ptr[v] == sz(g[v])) {
            ans.emplace_back(v);
            st.pop_back();
            continue;
        }
        used[g[v][ptr[v]].second] = true;
        st.emplace_back(g[v][ptr[v]].first);
    }
    for (int i = 0; i < m; ++i) {
        if (!used[i]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    for (int el : ans) cout << el + 1 << ' ';
    cout << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
