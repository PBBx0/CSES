#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
ll pref[1001][1001];
ll query(int i1, int j1, int i2, int j2) {
    i1--, j1--;
    return pref[i2][j2] - pref[i1][j2] - pref[i2][j1] + pref[i1][j1];
}
void solve() {
    int n, q;
    cin >> n >> q;
    int ar[n][n];
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            ar[i][j] = s[j] == '*';
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + ar[i][j];
        }
    }
    for (int i = 0; i < q; ++i) {
        int i1, j1, i2, j2;
        cin >> i1 >> j1 >> i2 >> j2;
        cout << query(i1, j1, i2, j2) << '\n';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}