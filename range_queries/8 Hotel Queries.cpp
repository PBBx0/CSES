#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    int N = 1;
    vector<int> t, b;
    ST(vector<int>& a) {
        b = a;
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            t[i + N] = i;
        }
        for (int i = N - 1; i > 0; --i) {
            t[i] = a[t[i + i]] >= a[t[i + i + 1]] ? t[i + i] : t[i + i + 1];
        }
    }
    void update(int p, int x) {
        b[p] += x;
        for (p = (p + N) >> 1; p > 0; p >>= 1) {
            t[p] = b[t[p + p]] >= b[t[p + p + 1]] ? t[p + p] : t[p + p + 1];
        }
    }
    int get(int x) {
        if (b[t[1]] < x) return -1;
        int v = 1;
        while (v < N) {
            if (b[t[v + v]] >= x) v = v + v;
            else v = v + v + 1;
        }
        return t[v];
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ST st(a);
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        int p = st.get(x);
        cout << p + 1 << '\n';
        if (p == -1) continue;
        st.update(p, -x);
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