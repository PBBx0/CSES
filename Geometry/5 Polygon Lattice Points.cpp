#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
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
void solve() {
    int n;
    cin >> n;
    vector<r> p(n);
    for (r & el : p) cin >> el.x >> el.y;
    ll area = 0, cnt_border = 0;
    for (int i = 0; i < n; ++i) {
        r fst = p[i], snd = i == n - 1 ? p[0] : p[i + 1];
        area += fst ^ snd;
        r tmp = snd - fst;
        cnt_border += abs(__gcd(tmp.x, tmp.y));
    }
    area = abs(area) + 2;
    cout << (area - cnt_border) / 2 << ' ' << cnt_border << '\n';
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