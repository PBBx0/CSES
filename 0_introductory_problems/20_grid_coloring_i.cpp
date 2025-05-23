#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> field(n);
    for (auto& el : field) cin >> el;
    vector<string> ans(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        for (char x : "ABCD") {
            if (x == field[i][j]) continue;
            if (i > 0 && x == ans[i - 1][j]) continue;
            if (j > 0 && x == ans[i][j - 1]) continue;
            ans[i] += x;
            break;
        }
    }
    for (auto& el : ans) cout << el << '\n';
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