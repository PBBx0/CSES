#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e15;
struct ST {
    struct node {
        int ma = 0, ph = 0;
    };
    int N = 1;
    vector<node> t;
    ST(int n) {
        for (; N < n - 1; N <<= 1);
        t.resize(N << 1);
    }
    inline void clear() {
        for (int i = 1; i < N + N; ++i) t[i].ma = t[i].ph = 0;
    }
    inline int get_ma(int v) {
        return t[v].ma + t[v].ph;
    }
    inline void push(int v) {
        t[v].ma += t[v].ph;
        t[v + v].ph += t[v].ph;
        t[v + v + 1].ph += t[v].ph;
        t[v].ph = 0;
    }
    inline void recalc(int v) {
        t[v].ma = max(get_ma(v + v), get_ma(v + v + 1));
    }
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].ph += x;
            return;
        }
        int tm = (tr - tl) / 2 + tl;
        push(v);
        if (l < tm) update(v + v, tl, tm, l, r, x);
        if (tm < r) update(v + v + 1, tm, tr, l, r, x);
        recalc(v);
    }
    void update(int p, int x) {
        for (int v = 1, tl = 0, tr = N; v < N; ) {
            int tm = (tr - tl) / 2 + tl;
            push(v);
            if (p < tm) v = v + v;
            else v = v + v + 1;
        }
        for (t[p += N].ph += x; p > 1; p >>= 1) {
            recalc(p >> 1);
        }
    }
    inline bool ok() {
        return t[1].ma <= 1;
    }
};
struct event {
    ll x;
    int y1, y2, val, id;
    event(ll x = 0, int y1 = 0, int y2 = 0, int val = 1, int id = 0) : \
    x(x), y1(y1), y2(y2), val(val), id(id) {}
    friend bool operator < (const event & a, const event & b) {
        if (a.x != b.x) return a.x < b.x;
        return a.id < b.id;
    }
};
const int N = 1e5;
pair<char, int> a[N];
set<ll> yyy{-INF, 0, INF};
tuple<ll, ll, ll, ll> rect[N];
tuple<ll, int, ll, int> rct[N];
unordered_map<ll, int> mp;
event ev[2 * N];
set<event> ev2;
void solve() {
    auto start = clock();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i].first == 'D' && a[i + 1].first == 'U' ||
            a[i].first == 'U' && a[i + 1].first == 'D' ||
            a[i].first == 'R' && a[i + 1].first == 'L' ||
            a[i].first == 'L' && a[i + 1].first == 'R') {
            n = i + 1;
            break;
        }
    }
    ll y = 0;
    {/* create rectangles */
        y = 0;
        ll x = 0;
        for (int i = 0; i < n; ++i) {
            auto [d, k] = a[i];
            if (d == 'L') {
                rect[i] = {x - k + 1, y, x + 1, y + 1};
                yyy.insert(y), yyy.insert(y + 1);
                x -= k;
            } else if (d == 'R') {
                rect[i] = {x, y, x + k, y + 1};
                yyy.insert(y), yyy.insert(y + 1);
                x += k;
            } else if (d == 'D') {
                rect[i] = {x, y - k + 1, x + 1, y + 1};
                yyy.insert(y - k + 1), yyy.insert(y + 1);
                y -= k;
            } else if (d == 'U') {
                rect[i] = {x, y, x + 1, y + k};
                yyy.insert(y), yyy.insert(y + k);
                y += k;
            }
        }
    }
    mp.reserve(sz(yyy));
    int c = 0;
    for (ll yy : yyy) mp[yy] = c++;
    for (int i = 0; i < n; ++i) {
        auto [x1, y1, x2, y2] = rect[i];
        rct[i] = {x1, mp[y1], x2, mp[y2]};
    }



    ST st(c);
    for (int i = 0; i < n; ++i) {
        auto [x1, y1, x2, y2] = rct[i];
        ev[2 * i] = {x1, y1, y2, 1, 2 * i};
        ev[2 * i + 1] = {x2, y1, y2, -1, 2 * i + 1};
    }
    sort(ev, ev + n + n);
    auto check = [&](int m) {
        st.clear();
        ll pr = -INF;
        for (auto [x, y1, y2, v, id] : ev) {
            if (id >= 2 * m) continue;
            if (x != pr && !st.ok()) return false;
            if (y1 + 1 == y2) st.update(y1, v);
            else st.update(1, 0, st.N, y1, y2, v);
            pr = x;
        }
        return true;
    };
    auto check2 = [&]() {
        st.clear();
        ll pr = -INF;
        for (auto [x, y1, y2, v, _] : ev2) {
            if (x != pr && !st.ok()) return false;
            if (y1 + 1 == y2) st.update(y1, v);
            else st.update(1, 0, st.N, y1, y2, v);
            pr = x;
        }
        return true;
    };

    int lo = 1, hi = n + 1;
    while (hi - lo > 1) {
        int md = (hi - lo) / 2 + lo;
        if (check(md)) {
            lo = md;
        } else {
            hi = md;
        }
    }
    cerr << (::clock() - start) * 1e3 / CLOCKS_PER_SEC << '\n';
    int cnt = lo;
    if (cnt == n) {
        ll ans = 0;
        for (int i = 0; i < cnt; ++i) ans += a[i].second;
        cout << ans << '\n';
        return;
    }
    sort(ev, ev + n + n, [](auto & fst, auto & snd) {return fst.id < snd.id;});

    for (int i = 0; i < cnt; ++i) {
        ev2.insert(ev[2 * i]);
        ev2.insert(ev[2 * i + 1]);
    }

    lo = 0, hi = a[cnt].second;
    while (hi - lo > 1) {
        int md = (hi - lo) / 2 + lo;
        auto [x1, y1, x2, y2] = rect[cnt];
        auto [d, k] = a[cnt];
        if (d == 'L') {
            x1 += k - md;
        } else if (d == 'R') {
            x2 += md - k;
        } else if (d == 'D') {
            y1 = *(--yyy.upper_bound(y1 + k - md));
        } else if (d == 'U') {
            y2 = *yyy.lower_bound(y2 + md - k);
        }
        const event fst(x1, mp[y1], mp[y2], 1, cnt * 2);
        const event snd(x2, mp[y1], mp[y2], -1, cnt * 2 + 1);
        ev2.insert(fst);
        ev2.insert(snd);
        if (check2()) {
            lo = md;
        } else {
            hi = md;
        }
        ev2.erase(fst);
        ev2.erase(snd);
    }

    ll ans = lo;
    for (int i = 0; i < cnt; ++i) ans += a[i].second;
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
    solve();
    return 0;
}