#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct FT {
    vector<ll> t;
    FT(int n) : t(n) {}
    void update(int p, int x) {
        for (; p < sz(t); p |= p + 1) {
            t[p] += x;
        }
    }
    ll get(int p) {
        ll res = 0;
        for (; p > 0; p &= p - 1) {
            res += t[p - 1];
        }
        return res;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    FT ft(n);
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            ft.update(l, x);
            ft.update(r, -x);
        } else if (t == 2) {
            int p;
            cin >> p;
            p--;
            cout << a[p] + ft.get(p + 1) << '\n';
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