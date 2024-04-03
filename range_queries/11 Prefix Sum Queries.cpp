#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e15;
struct ST {
    int N = 1;
    struct node {
        ll mx = -INF, add = 0;
    };
    vector<node> t;
    ST(vector<ll>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            t[i + N].mx = a[i];
        }
        for (int i = N - 1; i > 0; --i) {
            t[i].mx = max(t[i + i].mx, t[i + i + 1].mx);
        }
    }
    ll get_mx(int v) {
        return t[v].mx + t[v].add;
    }
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].add += x;
            return;
        }
        int tm = (tl - tr) / 2 + tr;
        update(v + v, tl, tm, l, r, x);
        update(v + v + 1, tm, tr, l, r, x);
        t[v].mx = max(get_mx(v + v), get_mx(v + v + 1));
    }
    ll get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return -INF;
        if (tl >= l && tr <= r) {
            return get_mx(v);
        }
        int tm = (tl - tr) / 2 + tr;
        return t[v].add + max(get(v + v, tl, tm, l, r), get(v + v + 1, tm, tr, l, r));
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<ll> p(n + 1);
    for (int i = 0; i < n; ++i) p[i + 1] = p[i] + a[i];
    ST st(p);
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int pos, x;
            cin >> pos >> x;
            pos--;
            int add = x - a[pos];
            a[pos] += add;
            st.update(1, 0, st.N, pos + 1, n + 1, add);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            l--, r++;
            cout << st.get(1, 0, st.N, l, r) - st.get(1, 0, st.N, l, l + 1) << '\n';
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