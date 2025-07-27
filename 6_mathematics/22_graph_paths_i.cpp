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

const int MOD = 1e9 + 7;

struct mint {
    int v;

    mint() : v(0) {}
    mint(int x) : v(x) {
        if (v < 0) v += MOD;
    }

    void identity() {
        v = 1;
    }

    mint& operator+=(mint o) {
        v = v + o.v < MOD ? v + o.v : v + o.v - MOD;
        return *this;
    }

    mint& operator*=(mint o) {
        v = 1LL * v * o.v % MOD;
        return *this;
    }
};

mint operator+(mint a, mint b) {
    return a += b;
}

mint operator*(mint a, mint b) {
    return a *= b;
}

const int N = 100;
struct matrix {
    mint a[N][N];

    void identity() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = i == j ? 1 : 0;
            }
        }
    }

    matrix& operator*=(matrix& o) {
        mint res[N][N];
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
            res[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                res[i][j] += a[i][k] * o.a[k][j];
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
    matrix res;
    res.identity();
    for (; pw > 0; pw >>= 1, x *= x) if (pw & 1) res *= x;
    return res;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    matrix g{};
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a][b] += 1;
    }
    auto gn = binpow(g, k);
    cout << gn[0][n - 1].v << '\n';
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
