#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int INF = 1e6 + 5;
struct ST {
    int N = 1;
    struct node {
        int min = 0, len_min = 0, upd = 0;
        node(int l = 0) : len_min(l) {}
    };
    vector<node> t;
    ST(vector<int> pos) {
        for (; N < sz(pos) - 1; N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(pos) - 1; ++i) {
            t[i + N].len_min = pos[i + 1] - pos[i];
        }
        for (int i = N - 1; i > 0; --i) {
            t[i].len_min = t[i + i].len_min + t[i + i + 1].len_min;
        }
    }
    int get_min(int v) {
        return t[v].min + t[v].upd;
    }
    void recalc(int v) {
        t[v].min = min(get_min(v + v), get_min(v + v + 1));
        t[v].len_min = 0;
        if (t[v].min == get_min(v + v)) t[v].len_min += t[v + v].len_min;
        if (t[v].min == get_min(v + v + 1)) t[v].len_min += t[v + v + 1].len_min;
    }
    void push(int v) {
        t[v].min += t[v].upd;
        t[v + v].upd += t[v].upd;
        t[v + v + 1].upd += t[v].upd;
        t[v].upd = 0;
    }
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].upd += x;
            return;
        }
        int tm = (tr - tl) / 2 + tl;
        push(v);
        update(v + v, tl, tm, l, r, x), update(v + v + 1, tm, tr, l, r, x);
        recalc(v);
    }
    int get() {
        return INF + INF - t[1].len_min;
    }
};
struct event {
    int x, y1, y2, v;
    event(int x, int y1, int y2, int v) : x(x), y1(y1), y2(y2), v(v) {}
};
void solve() {
    int n;
    cin >> n;
    vector<event> ev;
    set<int> s{-INF, INF};
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ev.emplace_back(x1, y1, y2, 1);
        ev.emplace_back(x2, y1, y2, -1);
        s.insert(y1), s.insert(y2);
    }
    vector<int> pos;
    unordered_map<int, int> mp;
    mp.reserve(sz(s));
    int c = 0;
    for (int el : s) {
        pos.emplace_back(el);
        mp[el] = c++;
    }
    ST st(pos);
    sort(ev.begin(), ev.end(), [&](auto fst, auto snd) {
        return fst.x < snd.x;
    });
    int pr = -INF;
    ll res = 0;
    for (auto [x, y1, y2, v] : ev) {
        res += 1LL * (x - pr) * st.get();
        st.update(1, 0, st.N, mp[y1], mp[y2], v);
        pr = x;
    }
    cout << res << '\n';
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