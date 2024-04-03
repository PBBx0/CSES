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
    friend ll len(const r & a) {
        return a.x * a.x + a.y * a.y;
    }
};
vector<r> hull;
void convex_hull(vector<r> pol) {
    r p0(1e10, 1e10);
    for (r el : pol) {
        if (el.y < p0.y || (el.y == p0.y && el.x < p0.x)) p0 = el;
    }
    sort(pol.begin(), pol.end(), [&](r fst, r snd) {
        ll t = fst - p0 ^ snd - p0;
        if (t != 0) return t > 0;
        return len(fst - p0) < len(snd - p0);
    });
    for (r v : pol) {
        while (sz(hull) >= 2 && (hull.back() - hull[sz(hull) - 2] ^ v - hull.back()) <= 0)
            hull.pop_back();
        hull.push_back(v);
    }
}
bool on_segment(r a, r b, r p) {
    return (p - a ^ b - a) == 0 && (a - p) * (b - p) <= 0;
}
bool point_onto_hull(r p) {
    if (on_segment(hull[0], hull[1], p) || on_segment(hull[0], hull.back(), p)) return true;
    r p0 = hull[0];
    r v = p - p0, v1 = hull[1] - p0, v2 = hull.back() - p0;
    if ((v1 ^ v) < 0 || (v2 ^ v) > 0) return false;
    int lo = 1, hi = sz(hull) - 1;
    while (hi - lo > 1) {
        int md = (hi - lo) / 2 + lo;
        if ((hull[md] - p0 ^ v) >= 0) {
            lo = md;
        } else {
            hi = md;
        }
    }
    return on_segment(hull[lo], hull[hi], p) || on_segment(hull[lo], hull[lo - 1], p);
}
void solve() {
    int n;
    cin >> n;
    vector<r> a(n);
    for (r & el : a) cin >> el.x >> el.y;
    convex_hull(a);
    vector<r> b;
    for (r el : a) if (point_onto_hull(el)) b.emplace_back(el);
    cout << sz(b) << '\n';
    for (r el : b) cout << el.x << ' ' << el.y << '\n';
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