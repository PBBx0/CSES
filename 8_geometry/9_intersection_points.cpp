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

struct FT {
    vector<int> t;

    FT(int n) : t(n) {}

    int get(int pos) {
        int res = 0;
        for (; pos > 0; pos &= pos - 1) res += t[pos - 1];
        return res;
    }

    int get(int l, int r) {
        return get(r) - get(l);
    }

    void upd(int pos, int x) {
        for (; pos < sz(t); pos |= pos + 1) t[pos] += x;
    }
};

struct event {
    int tp;
    int x;
    int y1, y2;
};

const int T = 1e6;
void solve() {
    int n;
    cin >> n;
    vector<event> a;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += T, y1 += T, x2 += T, y2 += T;
        if (x1 == x2) {
            a.emplace_back(0, x1, min(y1, y2), max(y1, y2));
        } else {
            a.emplace_back(1, min(x1, x2), y1, y2);
            a.emplace_back(2, max(x1, x2), y1, y2);
        }
    }
    sort(all(a), [](auto lhs, auto rhs) {
        return lhs.x < rhs.x;
    });
    FT ft(T + T + 1);
    ll ans = 0;
    for (auto [tp, x, y1, y2] : a) {
        if (tp == 0) {
            ans += ft.get(y1, y2);
        } else if (tp == 1) {
            ft.upd(y1, +1);
        } else if (tp == 2) {
            ft.upd(y1, -1);
        }
    }
    cout << ans << '\n';
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
