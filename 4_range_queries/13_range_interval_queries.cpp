#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

struct MSTree {
    int N = 1;
    vector<vector<int>> t;

    explicit MSTree(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) t[i + N] = {a[i]};
        for (int i = N - 1; i > 0; --i) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }

    int get(int l, int r, int lo, int hi) {
        int ans = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                ans += lower_bound(all(t[l]), hi) - lower_bound(all(t[l]), lo);
                ++l;
            }
            if (r & 1) {
                --r;
                ans += lower_bound(all(t[r]), hi) - lower_bound(all(t[r]), lo);
            }
        }
        return ans;
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    MSTree ms(a);
    for (int i = 0; i < q; ++i) {
        int l, r, lo, hi;
        cin >> l >> r >> lo >> hi;
        --l, ++hi;
        cout << ms.get(l, r, lo, hi) << '\n';
    }
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
