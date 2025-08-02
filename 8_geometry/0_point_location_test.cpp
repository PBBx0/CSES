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

istream& operator>>(istream& in, R& p) {
    return in >> p.x >> p.y;
}


void solve() {
    R a, b, c;
    cin >> a >> b >> c;
    ll r = cross(b, a, c);
    cout << (r == 0 ? "TOUCH" : r > 0 ? "LEFT" : "RIGHT") << '\n';
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
