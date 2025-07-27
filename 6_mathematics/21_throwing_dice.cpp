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

template <int N>
struct matrix {
    array<array<mint, N>, N> a{};

    void identity() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = i == j ? 1 : 0;
            }
        }
    }

    matrix& operator*=(matrix& o) {
        array<array<mint, N>, N> res{};
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                res[i][j] += a[i][k] * o.a[k][j];
            }
        }
        a = res;
        return *this;
    }

    auto& operator[](int i) {
        return a[i];
    }
};

template <typename T>
T binpow(T x, ll pw) {
    T res;
    res.identity();
    for (; pw > 0; pw >>= 1, x *= x) if (pw & 1) res *= x;
    return res;
}

void solve() {
    ll n;
    cin >> n;
    matrix<6> F;
    F[1][0] = F[2][1] = F[3][2] = F[4][3] = F[5][4] = 1;
    F[0][5] = F[1][5] = F[2][5] = F[3][5] = F[4][5] = F[5][5] = 1;
    auto Fn = binpow(F, n);
    cout << Fn[5][5].v << '\n';
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
