#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    struct node {
        ll sum = 0, add = 0, d = 0;
    };
    int N = 1;
    vector<node> t;
    ST(vector<int>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) t[i + N].sum = a[i];
        for (int i = N - 1; i > 0; --i) t[i].sum = t[i + i].sum + t[i + i + 1].sum;
    }
    ll get(int v, int tl, int tr) {
        return t[v].sum + t[v].add * (tr - tl) + t[v].d * (tr - tl + 1) * (tr - tl) / 2;// -1 to +1
    }
    void pull(int v, int tl, int tr) {
        int tm = (tr - tl) / 2 + tl;
        t[v].sum = get(v + v, tl, tm) + get(v + v + 1, tm, tr);
    }
    void push(int v, int tl, int tr) {
        t[v].sum = get(v, tl, tr);
        t[v + v].add += t[v].add;
        t[v + v + 1].add += t[v].add + t[v].d * (tr - tl) / 2;
        t[v].add = 0;
        t[v + v].d += t[v].d;
        t[v + v + 1].d += t[v].d;
        t[v].d = 0;
    }
    void update(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].d++;
            t[v].add += tl - l;// + 1
            return;
        }
        push(v, tl, tr);
        int tm = (tr - tl) / 2 + tl;
        update(v + v, tl, tm, l, r);
        update(v + v + 1, tm, tr, l, r);
        pull(v, tl, tr);
    }
    ll get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) {
            return get(v, tl, tr);
        }
        push(v, tl, tr);
        int tm = (tr - tl) / 2 + tl;
        return get(v + v, tl, tm, l, r) + get(v + v + 1, tm, tr, l, r);
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
        l--;
        if (t == 1) {
            st.update(1, 0, st.N, l, r);
        } else if (t == 2) {
            cout << st.get(1, 0, st.N, l, r) << '\n';
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