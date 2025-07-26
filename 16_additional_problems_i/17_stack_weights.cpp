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

const int INF = 1e9;

struct ST {
    int N = 1;
    vector<int> mn, mx, add;

    ST(int n) {
        while (N < n) N <<= 1;
        mn.resize(N << 1);
        mx.resize(N << 1);
        add.resize(N << 1);
    }

    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            add[v] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        update(v << 1 | 0, tl, tm, l, r, x);
        update(v << 1 | 1, tm, tr, l, r, x);
        mx[v] = max(add[v << 1 | 0] + mx[v << 1 | 0], add[v << 1 | 1] + mx[v << 1 | 1]);
        mn[v] = min(add[v << 1 | 0] + mn[v << 1 | 0], add[v << 1 | 1] + mn[v << 1 | 1]);
    }

    void update(int l, int r, int x) {
        update(1, 0, N, l, r, x);
    }

    pair<int, int> get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return {INF, -INF};
        if (tl >= l && tr <= r) return {mn[v] + add[v], mx[v] + add[v]};
        int tm = (tl + tr) / 2;
        auto [mn1, mx1] = get(v << 1 | 0, tl, tm, l, r);
        auto [mn2, mx2] = get(v << 1 | 1, tm, tr, l, r);
        return {min(mn1, mn2) + add[v], max(mx1, mx2) + add[v]};
    }

    auto get(int l, int r) {
        return get(1, 0, N, l, r);
    }
};

void solve() {
    int n;
    cin >> n;
    ST st(n);
    for (int i = 0; i < n; ++i) {
        int x, t;
        cin >> x >> t;
        --x;
        st.update(0, x + 1, t == 1 ? 1 : -1);
        auto [mn, mx] = st.get(0, n);
        if (mn >= 0) {
            cout << '>' << '\n';
        } else if (mx <= 0) {
            cout << '<' << '\n';
        } else {
            cout << '?' << '\n';
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
