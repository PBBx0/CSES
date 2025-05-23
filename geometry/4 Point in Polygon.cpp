#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
using ld = long double;
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
};
bool on_segment(r a, r b, r x) {
    return (b - a ^ x - a) == 0 && (a - x) * (b - x) <= 0;
}
vector<r> p;
int check(r a) {
    int ok = 0;
    for (int i = 0; i < sz(p); ++i) {
        r fst = p[i], snd = i + 1 < sz(p) ? p[i + 1] : p[0];
        if (on_segment(fst, snd, a)) return 2;
        if (fst.y > snd.y) swap(fst, snd);
        if (fst.y > a.y || snd.y <= a.y) continue;
        ll x = a.x, y = a.y;
        ll x1 = fst.x, x2 = snd.x;
        ll y1 = fst.y, y2 = snd.y;
        ld cur = x1 + (x2 - x1) * (y - y1) / ld(y2 - y1);
        if (cur >= x) ok = 1 - ok;
    }
    return ok;
}
void solve() {
    int n, q;
    cin >> n >> q;
    p.resize(n);
    for (auto & el : p) cin >> el.x >> el.y;
    for (int i = 0; i < q; ++i) {
        r cur;
        cin >> cur.x >> cur.y;
        int t = check(cur);
        if (t == 0) {
            cout << "OUTSIDE" << '\n';
        } else if (t == 1) {
            cout << "INSIDE" << '\n';
        } else if (t == 2) {
            cout << "BOUNDARY" << '\n';
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