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

int n, m;
vector<vector<int>> g;
vector<int> mt, col;

bool kuhn(int v, int c) {
    col[v] = c;
    for (int to : g[v]) {
        if (mt[to] == -1) {
            mt[to] = v;
            return true;
        }
    }
    for (int to : g[v]) {
        if (col[mt[to]] == c) continue;
        if (kuhn(mt[to], c)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}


void solve() {
    cin >> n >> m;
    g.resize(n);
    col.resize(n, -1);
    mt.resize(m, -1);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += kuhn(i, i);
    }
    cout << ans << '\n';
    for (int i = 0; i < m; ++i) {
        if (mt[i] != -1) {
            cout << mt[i] + 1 << ' ' << i + 1 << '\n';
        }
    }
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
