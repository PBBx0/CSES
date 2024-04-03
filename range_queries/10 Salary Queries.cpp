#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1 << 30;
struct ST {
    struct node {
        int l = -1, r = -1;
        int sum = 0;
    };
    vector<node> t;
    ST() : t(1) {}
    int get(int v, int tl, int tr, int l, int r) {
        if (v == -1 || tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) return t[v].sum;
        int tm = (tl - tr) / 2 + tr;
        return get(t[v].l, tl, tm, l, r) + get(t[v].r, tm, tr, l, r);
    }
    void update(int v, int tl, int tr, int pos, int x) {
        t[v].sum += x;
        if (tl + 1 == tr) return;
        int tm = (tl - tr) / 2 + tr;
        if (pos < tm) {
            if (t[v].l == -1) {
                t[v].l = sz(t);
                t.emplace_back();
            }
            update(t[v].l, tl, tm, pos, x);
        } else {
            if (t[v].r == -1) {
                t[v].r = sz(t);
                t.emplace_back();
            }
            update(t[v].r, tm, tr, pos, x);
        }
    }
};
void solve() {
    ST st;
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    for (int el : a) st.update(0, 0, N, el, 1);
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        if (t == '!') {
            int p, x;
            cin >> p >> x;
            p--;
            st.update(0, 0, N, a[p], -1);
            a[p] = x;
            st.update(0, 0, N, a[p], +1);
        } else if (t == '?') {
            int l, r;
            cin >> l >> r;
            cout << st.get(0, 0, N, l, r + 1) << '\n';
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