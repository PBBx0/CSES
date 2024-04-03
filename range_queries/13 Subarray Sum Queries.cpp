#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e15;
struct ST {
    int N = 1;
    struct node {
        ll mi = INF, ma = -INF, ans = 0, add = 0;
    };
    vector<node> t;
    ll get_ma(int v) {
        return t[v].ma + t[v].add;
    }
    ll get_mi(int v) {
        return t[v].mi + t[v].add;
    }
    void pull(int v) {
        t[v].mi = min(get_mi(v + v), get_mi(v + v + 1));
        t[v].ma = max(get_ma(v + v), get_ma(v + v + 1));
        t[v].ans = max({t[v + v].ans, t[v + v + 1].ans, get_ma(v + v + 1) - get_mi(v + v)});
    }
    ST(vector<ll>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            t[i + N].mi = t[i + N].ma = a[i];
        }
        for (int i = N - 1; i > 0; --i) {
            pull(i);
        }
    }
    ll get() {
        return t[1].ans;
    }
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].add += x;
            return;
        }
        int tm = (tr - tl) / 2 + tl;
        update(v + v, tl, tm, l, r, x);
        update(v + v + 1, tm, tr, l, r, x);
        pull(v);
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
        int pos, x;
        cin >> pos >> x;
        pos--;
        int add = x - a[pos];
        a[pos] += add;
        st.update(1, 0, st.N, pos + 1, n + 1, add);
        cout << st.get() << '\n';
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