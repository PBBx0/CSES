#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    struct node {
        ll sm = 0, sz = 1, add = 0, upd = -1;
    };
    int N = 1;
    vector<node> t;
    ll get(int v) {
        return t[v].upd == -1 ? t[v].sm + t[v].add * t[v].sz : (t[v].upd + t[v].add) * t[v].sz;
    }
    void pull(int v) {
        t[v].sz = t[v + v].sz + t[v + v + 1].sz;
        t[v].sm = get(v + v) + get(v + v + 1);
    }
    void push(int v) {
        if (t[v].upd != -1) {
            t[v + v].upd = t[v + v + 1].upd = t[v].upd;
            t[v + v].add = t[v + v + 1].add = t[v].add;
        } else {
            t[v + v].add += t[v].add;
            t[v + v + 1].add += t[v].add;
        }
        t[v].add = 0;
        t[v].upd = -1;
        pull(v);
    }
    ST(vector<int>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) t[i + N].sm = a[i];
        for (int i = N - 1; i > 0; --i) pull(i);
    }
    void add(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].add += x;
            return;
        }
        push(v);
        int tm = (tr - tl) / 2 + tl;
        add(v + v, tl, tm, l, r, x);
        add(v + v + 1, tm, tr, l, r, x);
        pull(v);
    }
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].add = 0;
            t[v].upd = x;
            return;
        }
        push(v);
        int tm = (tr - tl) / 2 + tl;
        update(v + v, tl, tm, l, r, x);
        update(v + v + 1, tm, tr, l, r, x);
        pull(v);
    }
    ll get_sum(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) return get(v);
        push(v);
        int tm = (tr - tl) / 2 + tl;
        return get_sum(v + v, tl, tm, l, r) + get_sum(v + v + 1, tm, tr, l, r);
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ST st(a);
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            st.add(1, 0, st.N, --l, r, x);
        } else if (t == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            st.update(1, 0, st.N, --l, r, x);
        } else if (t == 3) {
            int l, r;
            cin >> l >> r;
            cout << st.get_sum(1, 0, st.N, --l, r) << '\n';
        }
    }
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}