#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct MST {
    int N = 1;
    vector<vector<int>> t;
    MST(vector<int>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            t[i + N].emplace_back(a[i]);
        }
        for (int i = N - 1; i > 0; --i) {
            t[i].resize(sz(t[i + i]) + sz(t[i + i + 1]));
            std::merge(t[i + i].begin(), t[i + i].end(), t[i + i + 1].begin(), t[i + i + 1].end(), t[i].begin());
        }
    }
    inline int mget(int v, int x) {
        return int(std::lower_bound(t[v].begin(), t[v].end(), x) - t[v].begin());
    }
    int get_less(int l, int r, int x) {
        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += mget(l++, x);
            if (r & 1) res += mget(--r, x);
        }
        return res;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    unordered_map<int, int> prev;
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = prev.contains(a[i]) ? prev[a[i]] : -1;
        prev[a[i]] = i;
    }
    MST mst(b);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        cout << mst.get_less(l, r, l) << '\n';
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