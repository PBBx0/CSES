#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

struct seg_tree {
    int N = 1;
    vector<int> t;
    seg_tree(int n) {
        for (; N < n; N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < n; ++i) t[i + N] = 1;
        for (int i = N - 1; i > 0; --i) t[i] = t[i + i] + t[i + i + 1];
    }
    void update(int p) {
        for (t[p += N] = 0; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    int get_sum(int l, int r) {
        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
    int get(int k) {
        int v = 1;
        while (v < N) {
            if (t[v + v] < k) {
                k -= t[v + v];
                v = v + v + 1;
            } else {
                v = v + v;
            }
        }
        return v - N;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    seg_tree st(n);
    int cur = k;
    for (int i = 0; i < n; ++i) {
        int v = st.get(cur % (n - i) + 1);
        cout << v + 1 << ' ';
        st.update(v);
        cur = st.get_sum(0, v) + k;
    }
    cout << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}