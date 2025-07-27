#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;


const int N = 100;

struct matrix {
    ll a[N][N];

    void identity() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = i == j ? 0 : -1;
            }
        }
    }

    matrix& operator*=(const matrix& o) {
        ll res[N][N];
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
            ll& x = res[i][j];
            x = -1;
            for (int k = 0; k < N; ++k) {
                if (a[i][k] == -1 || o.a[k][j] == -1) continue;
                if (x == -1 || a[i][k] + o.a[k][j] < x) {
                    x = a[i][k] + o.a[k][j];
                }
            }
        }
        swap(a, res);
        return *this;
    }

    auto& operator[](int i) {
        return a[i];
    }
};

matrix binpow(matrix x, ll pw) {
    matrix res{};
    res.identity();
    for (; pw > 0; pw >>= 1, x *= x) if (pw & 1) res *= x;
    return res;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    matrix g{};
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) g[i][j] = -1;
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        --a, --b;
        if (g[a][b] == -1 || g[a][b] > c) g[a][b] = c;
    }
    auto gn = binpow(g, k);
    cout << gn[0][n - 1] << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
