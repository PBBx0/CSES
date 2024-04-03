#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1002;
bool avail[N][N], used[N][N];
const vector<pair<int, int>> shift = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};
void dfs(int i, int j) {
    avail[i][j] = false;
    for (auto [dx, dy] : shift) {
        if (avail[i + dx][j + dy]) {
            dfs(i + dx, j + dy);
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char tmp;
            cin >> tmp;
            avail[i][j] = tmp == '.';
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) if (avail[i][j]) {
            dfs(i, j);
            res++;
        }
    }
    cout << res << '\n';
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