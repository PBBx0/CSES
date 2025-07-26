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
    int N = 1;
    vector<ll> t, add, upd;

    explicit ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        add.resize(N << 1);
        upd.resize(N << 1, -1);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) t[i] = t[i << 1 | 0] + t[i << 1 | 1];
    }

    void push(int v, int tl, int tr) {
        if (upd[v] != -1) {
            upd[v << 1 | 0] = upd[v << 1 | 1] = upd[v];
            add[v << 1 | 0] = add[v << 1 | 1] = 0;
            t[v] = upd[v] * (tr - tl);
            upd[v] = -1;
        }
        if (add[v] != 0) {
            add[v << 1 | 0] += add[v];
            add[v << 1 | 1] += add[v];
            t[v] += add[v] * (tr - tl);
            add[v] = 0;
        }
    }

    ll get_sum(int v, int tl, int tr) {
        return add[v] * (tr - tl) + (upd[v] == -1 ? t[v] : upd[v] * (tr - tl));
    }

    ll get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) {
            return get_sum(v, tl, tr);
        }
        int tm = (tl + tr) / 2;
        push(v, tl, tr);
        return get(v << 1 | 0, tl, tm, l, r) +
               get(v << 1 | 1, tm, tr, l, r);
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    void plus(int v, int tl, int tr, int l, int r, ll x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            add[v] += x;
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        plus(v << 1 | 0, tl, tm, l, r, x);
        plus(v << 1 | 1, tm, tr, l, r, x);
        t[v] = get_sum(v << 1 | 0, tl, tm) + get_sum(v << 1 | 1, tm, tr);
    }

    void plus(int l, int r, ll x) {
        plus(1, 0, N, l, r, x);
    }

    void update(int v, int tl, int tr, int l, int r, ll x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            add[v] = 0;
            upd[v] = x;
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        update(v << 1 | 0, tl, tm, l, r, x);
        update(v << 1 | 1, tm, tr, l, r, x);
        t[v] = get_sum(v << 1 | 0, tl, tm) + get_sum(v << 1 | 1, tm, tr);

    }

    void update(int l, int r, ll x) {
        update(1, 0, N, l, r, x);
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ST sgt(a);
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            sgt.plus(l, r, x);
        } else if (tp == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            sgt.update(l, r, x);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            cout << sgt.get(l, r) << '\n';
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
