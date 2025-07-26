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

struct ST {
    struct node {
        ll mxpref = 0, mxsuf = 0, mx = 0, sm = 0;
    };

    node merge(const node& a, const node& b) {
        return {
                max(a.mxpref, a.sm + b.mxpref),
                max(b.mxsuf, b.sm + a.mxsuf),
                max({a.mx, b.mx, a.mxsuf + b.mxpref}),
                a.sm + b.sm
        };
    }

    int N =  1;
    vector<node> t;

    explicit ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            t[i + N].sm = a[i];
            if (a[i] > 0) t[i + N].mxpref = t[i + N].mxsuf = t[i + N].mx = a[i];
        }
        for (int i = N - 1; i > 0; --i) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void update(int pos, int x) {
        pos += N;
        t[pos].sm = x;
        t[pos].mxpref = t[pos].mxsuf = t[pos].mx = max(0, x);
        for (pos >>= 1; pos > 0; pos >>= 1)
            t[pos] = merge(t[pos << 1], t[pos << 1 | 1]);
    }

    ll get(int l, int r) {
        node left, right;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = merge(left, t[l++]);
            if (r & 1) right = merge(t[--r], right);
        }
        return merge(left, right).mx;
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ST st(a);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << st.get(l, r) << '\n';
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
