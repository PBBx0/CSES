#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct r {
    ll x, y;
    r(ll x = 0, ll y = 0) : x(x), y(y) {}
    ll operator^(const r &a) const {
        return x * a.y - y * a.x;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<r> p(n);
    for (r & el : p) cin >> el.x >> el.y;
    ll a = p.back() ^ p[0];
    for (int i = 1; i < n; ++i) {
        a += p[i - 1] ^ p[i];
    }
    cout << abs(a) << '\n';
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