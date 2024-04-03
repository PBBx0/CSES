#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 20, MOD = 1e9 + 7;
int dp[N][1 << N];
vector<int> g[N];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
    }
    dp[0][1] = 1;
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int v = 0; v < n; ++v) if (dp[v][mask]) {
            for (int to : g[v]) {
                int tmp = 1 << to;
                if ((mask & tmp) == 0) {
                    int& x = dp[to][mask ^ tmp];
                    x += dp[v][mask];
                    if (x >= MOD) x -= MOD;
                }
            }
        }
    }
    cout << dp[n - 1][(1 << n) - 1];
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