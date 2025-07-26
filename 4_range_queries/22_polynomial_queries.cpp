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
    vector<ll> t, start, step;

    explicit ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1), start.resize(N << 1), step.resize(N << 1);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) t[i] = t[i << 1 | 0] + t[i << 1 | 1];
    }

    ll get_sum(int v, int tl, int tr) {
        return t[v] + start[v] * (tr - tl) + step[v] * (tr - tl) * (tr - tl - 1) / 2;
    }

    void push(int v, int tl, int tr) {
        if (start[v] == 0 && step[v] == 0) return;
        int tm = (tr + tl) / 2;
        start[v << 1 | 0] += start[v];
        start[v << 1 | 1] += start[v] + (tm - tl) * step[v];
        step[v << 1 | 0] += step[v];
        step[v << 1 | 1] += step[v];
        t[v] = get_sum(v, tl, tr);
        start[v] = step[v] = 0;
    }

    ll get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) return get_sum(v, tl, tr);
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return get(v << 1 | 0, tl, tm, l, r) +
               get(v << 1 | 1, tm, tr, l, r);
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    void update(int v, int tl, int tr, int l, int r, ll strt, ll stp) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            step[v] += stp;
            start[v] += strt + stp * (tl - l);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        update(v << 1 | 0, tl, tm, l, r, strt, stp);
        update(v << 1 | 1, tm, tr, l, r, strt, stp);
        t[v] = get_sum(v << 1 | 0, tl, tm) + get_sum(v << 1 | 1, tm, tr);
    }

    void update(int l, int r, ll strt, ll stp) {
        update(1, 0, N, l, r, strt, stp);
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ST st(a);
    for (int i = 0; i < q; ++i) {
        int t, l, r;
        cin >> t >> l >> r;
        --l;
        if (t == 1) {
            st.update(l, r, 1, 1);
        } else {
            cout << st.get(l, r) << '\n';
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
