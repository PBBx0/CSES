#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 100;
struct dst {
    ll d[N][N];
    dst(bool flag = true) {
        for (auto & i : d) for (auto & j : i) j = -1;
        if (flag) {
            for (int i = 0; i < N; ++i) d[i][i] = 0;
        }
    }
    void merge(const dst & a) {
        ll d2[N][N];
        for (auto & i : d2) for (auto & j : i) j = -1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) if (d[i][j] != -1) {
                for (int k = 0; k < N; ++k) if (a.d[j][k] != -1) {
                    if (d2[i][k] == -1 || d2[i][k] > d[i][j] + a.d[j][k])
                        d2[i][k] = d[i][j] + a.d[j][k];
                }
            }
        }
        swap(d, d2);
    }
};
dst pow(dst a, ll pw) {
    dst res;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res.merge(a);
        a.merge(a);
    }
    return res;
}
void solve() {
    int n, m, k;
    dst cur(false);
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        ll & x = cur.d[a][b];
        if (x == -1 || x > c) x = c;
    }
    auto r = pow(cur, k);
    cout << r.d[0][n - 1] << '\n';
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