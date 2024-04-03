#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int T = 6;
const ll MOD = 1e9 + 7;
struct matrix {
    vector<vector<ll>> m;
    matrix() {
        m.resize(T, vector<ll>(T));
        for (int i = 0; i < T; ++i) m[i][i] = 1;
    }
    void operator *= (const matrix & a) {
        ll m2[T][T];
        for (int i = 0; i < T; ++i) {
            for (int j = 0; j < T; ++j) {
                m2[i][j] = 0;
                for (int x = 0; x < T; ++x) {
                    m2[i][j] = (m2[i][j] + m[i][x] * a.m[x][j] % MOD) % MOD;
                }
            }
        }
        for (int i = 0; i < T; ++i) {
            for (int j = 0; j < T; ++j) {
                m[i][j] = m2[i][j];
            }
        }
    }
    ll get() {
        return m[T - 1][T - 1];
    }
};
matrix power(matrix a, ll pw) {
    matrix res;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res *= a;
        a *= a;
    }
    return res;
}
void solve() {
    matrix cur;
    cur.m = {
            {0, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1},
    };
    ll n;
    cin >> n;
    cout << power(cur, n).get() << '\n';
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