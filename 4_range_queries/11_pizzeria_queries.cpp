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

const int INF = 1e9 + 7;

struct ST {
    int N = 1;
    vector<int> t;

    explicit ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1, INF);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) t[i] = min(t[i << 1], t[i << 1 | 1]);
    }

    void update(int pos, int add) {
        t[pos += N] += add;
        for (pos >>= 1; pos > 0; pos >>= 1) t[pos] = min(t[pos << 1], t[pos << 1 | 1]);
    }

    int get(int l, int r) {
        int res = INF;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> b(n), c(n);
    for (int i = 0; i < n; ++i) b[i] = a[i] - i, c[i] = a[i] + i;
    ST st1(b), st2(c);
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int pos, x;
            cin >> pos >> x;
            --pos;
            int delta = x - a[pos];
            a[pos] += delta;
            st1.update(pos, delta);
            st2.update(pos, delta);
        } else {
            int pos;
            cin >> pos;
            --pos;
            cout << min(pos + st1.get(0, pos + 1), -pos + st2.get(pos, n)) << '\n';
        }
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
