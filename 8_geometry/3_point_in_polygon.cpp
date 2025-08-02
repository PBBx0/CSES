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

istream& operator>>(istream& in, R& p) {
    return in >> p.x >> p.y;
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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<R> poly(n);
    for (R& el : poly) cin >> el;
    for (int i = 0; i < m; ++i) {
        R a;
        cin >> a;
        int res = check_point_in_polygon(poly, a);
        cout << (res == 0 ? "OUTSIDE" : res == 1 ? "INSIDE" : "BOUNDARY") << '\n';
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
