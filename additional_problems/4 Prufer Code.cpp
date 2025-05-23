#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    int N = 1;
    vector<int> t, b;
    ST(int n) : b(n) {
        for (; N < n; N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < n; ++i) t[i + N] = i;
        for (int i = N - 1; i > 0; --i) {
            if (b[t[i + i]] <= b[t[i + i + 1]]) {
                t[i] = t[i + i];
            } else {
                t[i] = t[i + i + 1];
            }
        }
    }
    void update(int p, int x) {
        b[p] += x;
        for (p = (p + N) >> 1; p > 0; p >>= 1) {
            if (b[t[p + p]] <= b[t[p + p + 1]]) {
                t[p] = t[p + p];
            }  else {
                t[p] = t[p + p + 1];
            }
        }
    }
    int get() {
        return t[1];
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n - 2);
    for (int & el : a) {
        cin >> el;
        --el;
    }
    ST st(n);
    for (int el : a) st.update(el, 1);
    for (int i = 0; i < n - 2; ++i) {
        int x = st.get();
        cout << x + 1 << ' ' << a[i] + 1 << '\n';
        st.update(x, 1);
        st.update(a[i], -1);
    }
    st.update(a.back(), 1);
    cout << st.get() + 1 << ' ' << a.back() + 1 << '\n';
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