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

    explicit FT(int n) : t(n) {}

    int get(int p) {
        int res = 0;
        for (; p > 0; p &= p - 1) res += t[p - 1];
        return res;
    }

    void upd(int p, int x) {
        for (; p < sz(t); p |= p + 1) t[p] += x;
    }
};


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), xx;
    for (int& el : a) {
        cin >> el;
        xx.emplace_back(el);
    }
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    for (int& el : a) el = std::lower_bound(xx.begin(), xx.end(), el) - xx.begin();

    int c = sz(xx);
    vector<int> nxt(c, -1);
    vector<array<int, 3>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][0] >> queries[i][1];
        --queries[i][0];
        queries[i][2] = i;
    }
    vector<int> ans(q);
    sort(all(queries));
    FT ft(n);
    for (int i = n - 1; i >= 0; --i) {
        int el = a[i];
        if (nxt[el] != -1) ft.upd(nxt[el], -1);
        ft.upd(i, 1);
        nxt[el] = i;
        while (!queries.empty() && queries.back()[0] == i) {
            auto [l, r, id] = queries.back();
            queries.pop_back();
            ans[id] = ft.get(r);
        }
    }
    for (int el : ans) cout << el << '\n';
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
