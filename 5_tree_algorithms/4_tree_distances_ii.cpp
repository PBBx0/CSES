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
vector<ll> ans, s;

ll dist0 = 0;
int n;

void dfs0(int v, int par, int cur_dist) {
    dist0 += cur_dist;
    for (int to : g[v]) if (to != par) {
        dfs0(to, v, cur_dist + 1);
        s[v] += s[to];
    }
    ++s[v];
}


void dfs(int v, int par, ll upper) {
    ans[v] = upper;
    for (int to : g[v]) if (to != par) {
        dfs(to, v, upper - s[to] + n - s[to]);
    }
}


void solve() {
    cin >> n;
    g.resize(n);
    s.resize(n), ans.resize(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs0(0, 0, 0);
    dfs(0, 0, dist0);
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
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
