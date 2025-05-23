#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
const int N = 1e6 + 10;
using ll = int64_t;
struct FT {
    vector<int> t;
    FT(int n) : t(n) {}
    void upd(int p, int x) {
        for (; p < sz(t); p |= p + 1) t[p] += x;
    }
    void update(int l, int r) {
        upd(l, 1), upd(r, -1);
    }
    int get(int p) {
        int res = 0;
        for (p++; p > 0; p &= p - 1) res += t[p - 1];
        return res;
    }
};
struct ev {
    int x, y1, y2, tp;
    ev(int x = 0, int y1 = 0, int y2 = 0, int tp = 0) : \
    x(x), y1(y1), y2(y2), tp(tp) {}
};
void solve() {
    vector<ev> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += N, y1 += N, x2 += N, y2 += N;
        if (x1 == x2) {
            a.emplace_back(x1, y1, y2, 0);
        } else {
            a.emplace_back(x1, y1, y2, -1);
            a.emplace_back(x2, y1, y2, 1);
        }
    }
    FT ft(N * 2);
    sort(a.begin(), a.end(), [](auto fst, auto snd) {
        return fst.x < snd.x;
    });
    ll res = 0;
    for (auto [x, y1, y2, tp] : a) {
        if (tp == 0) {
            ft.update(y1, y2 + 1);
        } else {
            res += tp * ft.get(y1);
        }
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