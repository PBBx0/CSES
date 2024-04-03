#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    struct node {
        int upd = 0, mn = 0, mx = 0;
    };
    vector<node> t;
    int N = 1;
    ST(int n) {
        for (; N < n; N <<= 1);
        t.resize(N << 1);
    }
    int get_mn(int v) {
        return t[v].mn + t[v].upd;
    }
    int get_mx(int v) {
        return t[v].mx + t[v].upd;
    }
    void recalc(int v) {
        t[v].mn = min(get_mn(v + v), get_mn(v + v + 1));
        t[v].mx = max(get_mx(v + v), get_mx(v + v + 1));
    }
    void push(int v) {
        t[v].mn += t[v].upd;
        t[v].mx += t[v].upd;
        t[v + v].upd += t[v].upd;
        t[v + v + 1].upd += t[v].upd;
        t[v].upd = 0;
    }
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].upd += x;
            return;
        }
        push(v);
        int tm = (tr - tl) / 2 + tl;
        update(v + v, tl, tm, l, r, x);
        update(v + v + 1, tm, tr, l, r, x);
        recalc(v);
    }
};
const int N = 2e5 + 10;
void solve() {
    ST st(N);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, c;
        cin >> x >> c;
        if (c == 2) c = -1;
        st.update(1, 0, st.N, 0, x + 1, c);
        if (st.get_mn(1) >= 0) {
            cout << '>' << '\n';
        }  else if (st.get_mx(1) <= 0) {
            cout << '<' << '\n';
        } else {
            cout << '?' << '\n';
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