#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int MOD = 1e9 + 7;

int sum(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

struct FT {
    vector<int> t;

    explicit FT(int n) : t(n) {}

    void add(int pos, int x) {
        for (; pos < sz(t); pos |= pos + 1) t[pos] = sum(t[pos], x);
    }

    int get(int pos) {
        int res = 0;
        for (; pos > 0; pos &= pos - 1) res = sum(res, t[pos - 1]);
        return res;
    }

    int get(int l, int r) {
        return sum(get(r), MOD - get(l));
    }
};


void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> xx;
    for (int& el : a) {
        cin >> el;
        xx.emplace_back(el);
    }
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    for (int& el : a) el = lower_bound(all(xx), el) - xx.begin() + 1;

    FT ft(sz(xx) + 2);
    ft.add(0, 1);

    int ans = 0;
    for (int x : a) {
        int cur = ft.get(x);
        ans = sum(ans, cur);
        ft.add(x, cur);
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}