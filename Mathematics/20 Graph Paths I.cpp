#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 100;
const ll MOD = 1e9 + 7;
struct matrix {
    ll m[N][N];
    matrix(bool zeros = false) {
        for (int i = 0; i < N; ++i) m[i][i] = !zeros;
    }
    void operator *= (const matrix & a) {
        ll m2[N][N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ll & x = m2[i][j];
                x = 0;
                for (int k = 0; k < N; ++k) {
                    x = (x + m[i][k] * a.m[k][j]) % MOD;
                }
            }
        }
        swap(m, m2);
    }
};
matrix pow(matrix a, ll pw) {
    matrix res;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res *= a;
        a *= a;
    }
    return res;
}
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    matrix cur(true);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cur.m[a][b]++;
    }
    auto r = pow(cur, k);
    cout << r.m[0][n - 1] << '\n';
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