#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    struct node {
        ll sum = 0;
        int l = -1, r = -1;
        node(ll sum = 0, int l = -1, int r = -1) : sum(sum), l(l), r(r) {}
    };
    vector<node> t;
    int N = 1;
    ST(vector<int>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            t[i + N].sum = a[i];
        }
        for (int i = N - 1; i > 0; --i) {
            t[i].l = i + i, t[i].r = i + i + 1;
            t[i].sum = t[i + i].sum + t[i + i + 1].sum;
        }
    }
    ll get_sum(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) {
            return t[v].sum;
        }
        int tm = (tr - tl) / 2 + tl;
        return get_sum(t[v].l, tl, tm, l, r) + get_sum(t[v].r, tm, tr, l, r);
    }
    int update(int v, int tl, int tr, int pos, ll x) {
        if (tl > pos || tr <= pos) return v;
        if (tl + 1 == tr) {
            t.emplace_back(x);
            return sz(t) - 1;
        }
        int tm = (tr - tl) / 2 + tl, res = sz(t);
        t.emplace_back();
        t[res].l = update(t[v].l, tl, tm, pos, x);
        t[res].r = update(t[v].r, tm, tr, pos, x);
        t[res].sum = t[t[res].l].sum + t[t[res].r].sum;
        return res;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ST st(a);
    vector<int> ver{1};
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, pos, x;
            cin >> v >> pos >> x;
            v--, pos--;
            ver[v] = st.update(ver[v], 0, st.N, pos, x);
        } else if (t == 2) {
            int v, l, r;
            cin >> v >> l >> r;
            v--, l--;
            cout << st.get_sum(ver[v], 0, st.N, l, r) << '\n';
        } else if (t == 3) {
            int v;
            cin >> v;
            v--;
            ver.emplace_back(ver[v]);
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