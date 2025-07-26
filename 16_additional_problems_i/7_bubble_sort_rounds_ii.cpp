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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), xx;
    for (int& el : a) {
        cin >> el;
        xx.emplace_back(el);
    }
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    for (int& el : a) el = lower_bound(all(xx), el) - xx.begin();

    vector<int> left(n), right(n);
    set<pair<int, int>> s;
    FT ft(sz(xx)), plus(sz(xx));

    for (int i = 0; i < n; ++i) {
        left[i] += ft.get(sz(xx)) - ft.get(a[i] + 1);

        plus.upd(a[i] + 1, 1);
        right[i] -= plus.get(a[i] + 1);

        s.emplace(a[i], i);

        ft.upd(a[i], 1);

        if (sz(s) > k) {
            auto j = s.begin()->second;
            s.erase(s.begin());
            ft.upd(a[j], -1);
            right[j] += plus.get(a[j] + 1);
        }
    }
    while (!s.empty()) {
        auto j = s.begin()->second;
        s.erase(s.begin());
        right[j] += plus.get(a[j] + 1);
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
//        cerr << left[i] << ' ' << right[i] << '\n';
        ans[i + right[i] - left[i]] = a[i];
    }
    for (int el : ans) cout << xx[el] << ' ';
    cout << '\n';
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
