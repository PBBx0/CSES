#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int INF = 1e9 + 7;
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
    void update(int pos, int add) {
        for (t[pos += N] += add; pos > 1; pos >>= 1) {
            t[pos >> 1] = min(t[pos], t[pos ^ 1]);
        }
    }
    int get(int l, int r) {
        int res = INF;
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
    vector<int> a(n), b(n), c(n);
    for (int& el : a) cin >> el;
    for (int i = 0; i < n; ++i) {
        b[i] = a[i] - i, c[i] = a[i] + i;
    }
    ST left(b), right(c);
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, x;
            cin >> p >> x;
            p--;
            int add = x - a[p];
            a[p] += add;
            left.update(p, add);
            right.update(p, add);
        } else if (t == 2) {
            int p;
            cin >> p;
            p--;
            int res = min(left.get(0, p) + p, right.get(p, n) - p);
            cout << res << '\n';
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