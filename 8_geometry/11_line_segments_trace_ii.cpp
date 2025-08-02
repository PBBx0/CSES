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

const ll INF = 1e18;

struct line {
    ll k = 0, b = -INF;

    ll operator()(ll x) {
        return k * x + b;
    }
};

struct li_chao {
    int N = 1;
    vector<line> t;

    li_chao(int n) {
        while (N < n) N <<= 1;
        t.resize(N << 1);
    }

    void add_line(int v, int tl, int tr, line L) {
        for (;;) {
            int tm = (tl + tr) / 2;
            if (t[v](tm) < L(tm)) swap(t[v], L);
            if (tl + 1 == tr || t[v].k == L.k) break;
            if (L.k < t[v].k) {
                v = v << 1 | 0;
                tr = tm;
            } else {
                v = v << 1 | 1;
                tl = tm;
            }
        }
    }

    void add_segment(int l, int r, line L) {
        int lb = l, rb = r, step = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1, step <<= 1) {
            if (l & 1) {
                add_line(l, lb, lb + step, L);
                ++l; lb += step;
            }
            if (r & 1) {
                --r;
                rb -= step;
                add_line(r, rb, rb + step, L);
            }
        }
    }

    void add_global(line L) {
        add_line(1, 0, N, L);
    }

    ll get(int x) {
        ll res = -INF;
        for (int p = x + N; p > 0; p >>= 1) res = max(res, t[p](x));
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    li_chao lc(m + 1);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ll k = (y2 - y1) / (x2 - x1);
        lc.add_segment(x1, x2 + 1, {k, y1 - k * x1});
    }
    for (int i = 0; i <= m; ++i) {
        ll r = lc.get(i);
        cout << (r == -INF ? -1 : r) << ' ';
    }
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
