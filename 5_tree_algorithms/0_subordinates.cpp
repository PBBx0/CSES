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

vector<vector<int>> g;
vector<int> s;

void dfs(int v) {
    for (int to : g[v]) {
        dfs(to);
        s[v] += s[to];
    }
    ++s[v];
}

void solve() {
    int n;
    cin >> n;
    g.resize(n), s.resize(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[--p].emplace_back(i);
    }
    dfs(0);
    for (int el : s) cout << el - 1 << ' ';
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
