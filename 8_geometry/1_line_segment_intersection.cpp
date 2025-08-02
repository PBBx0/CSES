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

struct R {
    ll x, y;

};

bool operator==(R a, R b) {
    return a.x == b.x && a.y == b.y;
}

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

ll sgn(ll x) {
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
    ll s1 = sgn(cross(c, a, b));
    ll s2 = sgn(cross(d, a, b));
    ll s3 = sgn(cross(a, c, d));
    ll s4 = sgn(cross(b, c, d));
    return s1 * s2 == -1 && s3 * s4 == -1;
}


void solve() {
    R a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << (segment_intersection(a, b, c, d) ? "YES" : "NO") << '\n';
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
    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
