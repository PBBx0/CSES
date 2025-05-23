#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
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
    void random() {
        x = rnd() % 100000;
        y = rnd() % 100000;
    }
};
ll len(const r & a) {
    return a * a;
}
r dir(0, 1);
bool cmp(r fst, r snd) {
    return fst * dir < snd * dir;
}
void solve() {
    int n;
    cin >> n;
    vector<r> a(n);
    for (r & el : a) cin >> el.x >> el.y;
    ll ans = 9e18;
    for (int _ = 0; _ < 10; ++_) {
        dir.random();
        sort(a.begin(), a.end(), cmp);
        for (int i = 1; i < n; ++i) {
            ll cur = len(a[i] - a[i - 1]);
            ans = min(ans, cur);
        }
    }
    cout << ans << '\n';
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