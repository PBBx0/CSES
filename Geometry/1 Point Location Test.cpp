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
void solve() {
    r a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    r v = b - a, u = c - a;
    ll t = sgn(u ^ v);
    string out;
    switch (t) {
        case -1:
            out = "LEFT";
            break;
        case 0:
            out = "TOUCH";
            break;
        case 1:
            out = "RIGHT";
            break;
    }
    cout << out << '\n';
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