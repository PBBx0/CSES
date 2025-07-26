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
    int v = 0;
    mint(int v) : v(v) {}
    mint() : v(0) {}

    mint& operator*=(const mint& o) {
        v = 1LL * v * o.v % MOD;
        return *this;
    }

    mint& operator+=(const mint& o) {
        v = v + o.v < MOD ? v + o.v : v + o.v - MOD;
        return *this;
    }
};

mint operator+(mint a, mint b) {
    return a += b;
}

mint operator*(mint a, mint b) {
    return a *= b;
}



template<typename T = mint>
struct m22 {
    array<array<T, 2>, 2> a;

    auto& operator[](int i) {
        return a[i];
    }

    m22& operator*=(const m22& o) {
        m22 res;
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                res[i][j] += a[i][k] * o.a[k][j];
            }
        }
        return *this = res;
    }

};

m22<mint> mexp(m22<mint> a, int pw) {
    m22 res;
    res[0][0] = res[1][1] = 1;
    for (; pw > 0; pw >>= 1, a *= a) if (pw & 1) res *= a;
    return res;
}

mint process(int n, int c) {
    m22<mint> a;
    a[0][1] = a[1][1] = 1;
    a[1][0] = c;
    auto res = mexp(a, n - 1);
    return res[0][0] * c + res[0][1] * c + res[1][0] + res[1][1];
}

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        mint ans = 1;

        vector<pair<int, int>> div;
        for (int j = 2; j * j <= k; ++j) {
            while (k % j == 0) {
                if (div.empty() || div.back().first != j) div.emplace_back(j, 1);
                else div.back().second += 1;
                k /= j;
            }
        }
        if (k > 1) div.emplace_back(k, 1);
        for (auto [x, cx] : div) {
            ans *= process(n, cx);
        }
        cout << ans.v << '\n';
    }
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
