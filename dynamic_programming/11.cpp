#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 502, INF = 1e7;
int dp[N][N];
void solve() {
    int a, b;
    cin >> a >> b;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dp[i][j] = INF;
        }
    }
    for (int i = 0; i < N; ++i) dp[i][i] = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            for (int k = 1; k < j; ++k) {
                dp[min(i, j)][max(i, j)] = min(dp[min(i, j)][max(i, j)],
                                               dp[min(i, k)][max(i, k)] + dp[min(i, j - k)][max(i, j - k)] + 1);
            }
            for (int k = 1; k < i; ++k) {
                dp[min(i, j)][max(i, j)] = min(dp[min(i, j)][max(i, j)],
                                               dp[min(k, j)][max(k, j)] + dp[min(i - k, j)][max(i - k, j)] + 1);
            }
        }
    }
    cout << dp[min(a, b)][max(a, b)] << '\n';
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