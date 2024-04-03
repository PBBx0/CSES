#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e16;
struct line {
    ll k, b;
    line(ll k = 0, ll b = INF) : k(k), b(b) {}
    ll intersect(line & l) {
        if (k == l.k) return -INF;
        return (l.b - b) / (k - l.k);
    }
    ll get(ll x) {
        return x * k + b;
    }
};
const int N = 1 << 20;
line t[N << 1];
ll get(ll x) {
    ll res = INF;
    for (ll p = x + N; p > 0; p >>= 1) res = min(res, t[p].get(x));
    return res;
}
void update(int v, int tl, int tr, line cur) {
    int tm = (tr - tl) / 2 + tl;
    if (t[v].get(tm) > cur.get(tm)) swap(t[v], cur);
    if (tl + 1 == tr) return;
    ll x = t[v].intersect(cur);
    if (x < tm) update(v + v, tl, tm, cur);
    else update(v + v + 1, tm, tr, cur);
}
void solve() {
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n), f(n);
    for (ll & el : a) cin >> el;
    for (ll & el : f) cin >> el;
    update(1, 0, N, line(x, 0));
    for (int i = 0; i < n - 1; ++i) {
        ll time = get(a[i]);
        update(1, 0, N, line(f[i], time));
    }
    cout << get(a[n - 1]) << '\n';
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