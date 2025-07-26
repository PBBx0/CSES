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
        int r = 0;
        for (; pos > 0; pos &= pos - 1) r += t[pos - 1];
        return r;
    }

    void upd(int pos, int x) {
        for (; pos < sz(t); pos |= pos + 1) t[pos] += x;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), xx;
    for (int& el : a) {
        cin >> el;
        xx.emplace_back(el);
    }
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    for (int& el : a) el = lower_bound(all(xx), el) - xx.begin();
    FT ft(sz(xx));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, i - ft.get(a[i] + 1));
        ft.upd(a[i], 1);
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
