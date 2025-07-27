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

template <typename T>
T binpow(T x, ll pw) {
    T res;
    res.identity();
    for (; pw > 0; pw >>= 1, x *= x) if (pw & 1) res *= x;
    return res;
}

istream& operator>>(istream& in, mint& x) {
    return in >> x.v;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector A(n, vector<mint>(m + 1));
    for (int i = 0; i < n; ++i) for (int j = 0; j <= m; ++j) {
        cin >> A[i][j];
    }
    vector<int> my_col(n, n);
    int row = 0;
    for (int j = 0; j < m; ++j) {
        int i = row;
        for (; i < n; ++i) {
            if (A[i][j].v != 0) break;
        }
        if (i == n) continue;
        my_col[row] = j;
        swap(A[i], A[row]);
        mint tmp = binpow(A[row][j], MOD - 2);
        for (int t = j; t <= m; ++t) A[row][t] *= tmp;
        for (i = row + 1; i < n; ++i) {
            if (A[i][j].v == 0) continue;
            tmp = MOD - A[i][j].v;
            for (int t = j; t <= m; ++t) A[i][t] += A[row][t] * tmp;
        }
        ++row;
    }
    for (int i = row; i < n; ++i) {
        if (A[i][m].v != 0) {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = row - 1; i >= 0; --i) {
        int j = my_col[i];
        assert(A[i][j].v == 1);
        for (int s = 0; s < i; ++s) {
            if (A[s][j].v == 0) continue;
            mint tmp = MOD - A[s][j].v;
            for (int t = j; t <= m; ++t) A[s][t] += tmp * A[i][t];
        }
    }
    vector<int> ans(m);
    for (int i = 0; i < row; ++i) {
        ans[my_col[i]] = A[i][m].v;
    }
    for (int el : ans) cout << el << ' ';
    cout << '\n';

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
