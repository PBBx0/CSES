#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct FT {
    vector<int> t;
    FT(int n) : t(n) {}
    void update(int p) {
        for (; p < sz(t); p |= p + 1) t[p]--;
    }
    int get(int p) {
        int res = p;
        for (; p > 0; p &= p - 1) {
            res += t[p - 1];
        }
        return res;
    }
    int find_idx(int p) {
        int lo = p, hi = sz(t);
        while (hi - lo > 1) {
            int md = (lo + hi) >> 1;
            if (get(md) <= p) {
                lo = md;
            } else {
                hi = md;
            }
        }
        return lo;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    FT ft(n);
    for (int& el : a) cin >> el;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        int idx = ft.find_idx(p);
        cout << a[idx] << ' ';
        ft.update(idx);
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