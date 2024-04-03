#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    int N = 1;
    vector<int> t;
    ST(vector<int>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            t[i + N] = a[i];
        }
        for (int i = N - 1; i > 0; --i) {
            t[i] = min(t[i + i], t[i + i + 1]);
        }
    }
    void upd(int p, int x) {
        for (t[p += N] = x; p > 1; p >>= 1) {
            t[p >> 1] = min(t[p], t[p ^ 1]);
        }
    }
    int get(int l, int r) {
        int res = 1e9;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
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
            int p, x;
            cin >> p >> x;
            st.upd(--p, x);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            cout << st.get(--l, r) << '\n';
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