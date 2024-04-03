#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
ll sgn(ll x) {
    return (x > 0) - (x < 0);
}
struct r {
    ll x, y;
    r(ll x = 0, ll y = 0) : x(x), y(y) {}
    ll operator ^ (const r & a) const {
        return x * a.y - y * a.x;
    }
    ll operator * (const r & a) const {
        return x * a.x + y * a.y;
    }
    r operator - (const r & a) const {
        return r(x - a.x, y - a.y);
    }
    r operator + (const r & a) const {
        return r(x + a.x, y + a.y);
    }
    r perp() const {
        return r(-y, x);
    }
    ll d2() const {
        return x * x + y * y;
    }
};
bool point_on_seg(r p, r a, r b) {
    return (p - a ^ b - a) == 0 && (a - p) * (b - p) <= 0;
}
void solve() {
    r a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    r ac = c - a, ab = b - a, ad = d - a;
    r ca = a - c, cd = d - c, cb = b - c;
    bool expr1 = sgn(ac ^ ab) * sgn(ad ^ ab) < 0;
    bool expr2 = sgn(ca ^ cd) * sgn(cb ^ cd) < 0;
    bool ok = expr1 && expr2 || point_on_seg(a, c, d)
            || point_on_seg(b, c, d) || point_on_seg(c, a, b) || point_on_seg(d, a, b);
    cout << (ok ? "YES" : "NO") << '\n';
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}