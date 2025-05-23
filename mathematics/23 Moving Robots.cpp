#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
using ld = long double;
const int T = 8, K = 1001;
ld p[K][T * T][T][T];
ld turn[T][T];
void solve() {
    int k;
    cin >> k;
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < T; ++j) {
            p[0][i * T + j][i][j] = 1;
            int cnt = 4 - (i == 0) - (i == T - 1) - (j == 0) - (j == T - 1);
            turn[i][j] = 1. / cnt;
        }
    }
    for (int trn = 1; trn <= k; ++trn) {
        for (int _ = 0; _ < T * T; ++_) {
            for (int i = 0; i < T; ++i) {
                for (int j = 0; j < T; ++j) {
                    ld & cur = p[trn][_][i][j];
                    if (i > 0) cur += p[trn - 1][_][i - 1][j] * turn[i - 1][j];
                    if (i < T - 1) cur += p[trn - 1][_][i + 1][j] * turn[i + 1][j];
                    if (j > 0) cur += p[trn - 1][_][i][j - 1] * turn[i][j - 1];
                    if (j < T - 1) cur += p[trn - 1][_][i][j + 1] * turn[i][j + 1];
                }
            }
        }
    }
    ld res = 0;
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < T; ++j) {
            ld cur = 1;
            for (int t = 0; t < T * T; ++t) {
                cur *= 1 - p[k][t][i][j];
            }
            res += cur;
        }
    }
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < T; ++j) {
            cerr << p[k][0][i][j] << ' ';
        }
        cerr << '\n';
    }
    cout << fixed << setprecision(30);
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}