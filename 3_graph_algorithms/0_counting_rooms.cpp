#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

int n, m;

vector<string> field;
vector<vector<bool>> used;


void dfs(int i, int j) {
    used[i][j] = true;
    for (auto [dx, dy] : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, 1}, {0, -1}}) {
        int i1 = i + dx, j1 = j + dy;
        if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) continue;
        if (used[i1][j1] || field[i1][j1] == '#') continue;
        dfs(i1, j1);
    }
}


void solve() {
    cin >> n >> m;
    field.resize(n);
    for (auto &el: field) cin >> el;
    used.resize(n, vector<bool>(m, false));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!used[i][j] && field[i][j] != '#') {
                ++ans;
                dfs(i, j);
            }
        }
    }
    cout << ans << '\n';
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