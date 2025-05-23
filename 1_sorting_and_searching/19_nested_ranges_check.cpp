#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

struct FT {
    int n;
    vector<int> t;

    explicit FT(int n) : n(n), t(n) {}

    void upd(int p, int x) {
        for (; p < n; p |= p + 1) t[p] += x;
    }

    int get(int p) {
        int res = 0;
        for (; p > 0; p &= p - 1) res += t[p - 1];
        return res;
    }

    int get(int l, int r) {
        return get(r) - get(l);
    }

    void clear() {
        fill(all(t), 0);
    }

};

struct event {
    int l, r, id;

    bool operator<(const event &o) const {
        return make_pair(l, -r) < make_pair(o.l, -o.r);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<event> seg(n);
    int j = 0;
    vector<int> xx;
    for (auto &[l, r, i]: seg) {
        cin >> l >> r;
        xx.emplace_back(l);
        xx.emplace_back(r);
        i = j++;
    }
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());

    sort(all(seg));
    for (auto &[l, r, id]: seg) {
        l = lower_bound(xx.begin(), xx.end(), l) - xx.begin();
        r = lower_bound(xx.begin(), xx.end(), r) - xx.begin();
    }

    const int T = sz(xx) + 1;

    vector<int> inner(n), outer(n);

    FT ft(T);
    for (auto [l, r, id] : seg) {
        outer[id] = ft.get(r, T);
        ft.upd(r, 1);
    }

    ft.clear();
    reverse(all(seg));
    for (auto [l, r, id] : seg) {
        inner[id] = ft.get(0, r + 1);
        ft.upd(r, 1);
    }

    for (int i = 0; i < n; ++i) cout << bool(inner[i]) << ' ';
    cout << '\n';
    for (int i = 0; i < n; ++i) cout << bool(outer[i]) << ' ';
    cout << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}