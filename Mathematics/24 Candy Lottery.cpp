#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
using ld = long double;
const int N = 102;
ld p[N][N];
void solve() {
    int n, k;
    cin >> n >> k;
    p[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < N; ++x) {
            for (int d = 1; d <= k; ++d) {
                if (x >= d) {
                    p[i + 1][x] += p[i][x] / k;
                } else {
                    p[i + 1][d] += p[i][x] / k;
                }
            }
        }
    }
    ld res = 0;
    for (int x = 0; x < N; ++x) res += x * p[n][x];
    cout << fixed << setprecision(6);
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