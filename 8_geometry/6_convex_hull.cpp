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

struct R { ll x, y; };

R operator-(R a, R b) {
    return {a.x - b.x, a.y - b.y};
}

ll operator*(R a, R b) {
    return a.x * b.x + a.y * b.y;
}

ll operator%(R a, R b) {
    return a.x * b.y - a.y * b.x;
}

ll cross(R a, R o, R b) {
    return (a - o) % (b - o);
}

ll sign(ll x) {
    return (x > 0) - (x < 0);
}

ll dist(R a, R b) {
    return hypot(abs(a.x - b.x), abs(a.y - b.y));
}

istream& operator>>(istream& in, R& p) {
    return in >> p.x >> p.y;
}

ostream& operator<<(ostream& out, R p) {
    return out << p.x << ' ' << p.y;
}

bool point_on_segment(R a, R b, R x) {
    return cross(a, x, b) == 0 && (a - x) * (b - x) <= 0;
}

bool segment_intersection(R a, R b, R c, R d) {
    if (point_on_segment(a, b, c) ||
            point_on_segment(a, b, d) ||
            point_on_segment(c, d, a) ||
            point_on_segment(c, d, b)) {
        return true;
    }
    ll s1 = sign(cross(c, a, b));
    ll s2 = sign(cross(d, a, b));
    ll s3 = sign(cross(a, c, d));
    ll s4 = sign(cross(b, c, d));
    return s1 * s2 == -1 && s3 * s4 == -1;
}

//0 -- outside, 1 -- inside, 2 -- boundary
int check_point_in_polygon(const vector<R>& p, R a) {
    static const ll INF = 2e9;
    int n = sz(p);
    int parity = 0;
    R b{INF, a.y + 1};
    for (int i = 0; i < n; ++i) {
        if (point_on_segment(p[i], p[(i + 1) % n], a)) return 2;
        parity ^= segment_intersection(p[i], p[(i + 1) % n], a, b);
    }
    return parity;
}

vector<R> convex_hull(vector<R>& p) {
    vector<R> hull;
    R p0 = *min_element(all(p), [](auto lhs, auto rhs){
        return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    });
    sort(all(p), [p0](R lhs, R rhs) {
        ll r1 = cross(lhs, p0, rhs);
        if (r1 != 0) return r1 > 0;
        return dist(lhs, p0) < dist(rhs, p0);
    });
    int s = 0;
    for (R pt : p) {
        while (s >= 2 && cross(pt, hull[s - 1], hull[s - 2]) <= 0) {
            hull.pop_back();
            --s;
        }
        hull.push_back(pt);
        ++s;
    }
    return hull;
}

bool point_onto_hull(const vector<R>& hull, R p) {
    int n = sz(hull);
    if (point_on_segment(hull[0], hull[1], p) || point_on_segment(hull[n - 1], hull[0], p)) {
        return true;
    }
    int lo = 1, hi = n - 1;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        (cross(hull[mid], hull[0], p) > 0 ? lo : hi) = mid;
    }
    return point_on_segment(hull[lo], hull[hi], p);
}

void solve() {
    int n;
    cin >> n;
    vector<R> pts(n);
    for (R& el : pts) cin >> el;
    auto hull = convex_hull(pts);
    vector<R> ans;
    for (R p : pts) {
        if (point_onto_hull(hull, p)) {
            ans.emplace_back(p);
        }
    }
    cout << sz(ans) << '\n';
    for (R el : ans) cout << el << '\n';
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
