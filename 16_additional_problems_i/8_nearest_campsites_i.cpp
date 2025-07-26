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

const int INF = 1e9 + 7;

struct ST {
    int N = 1;
    vector<int> t;
    ST(int n) {
        while (N < n) N <<= 1;
        t.resize(N << 1, INF);
    }

    int get(int l, int r) {
        int res = INF;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
    }

    void upd(int pos, int x) {
        pos += N;
        t[pos] = min(t[pos], x);
        for (pos >>= 1; pos > 0; pos >>= 1)
            t[pos] = min(t[pos << 1 | 0], t[pos << 1 | 1]);
    }

    void clear() {
        fill(all(t), INF);
    }
};

const int L = 1e6 + 1;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n), b(m);
    for (auto& [x, y] : a) cin >> x >> y;
    for (auto& [x, y] : b) cin >> x >> y;

    vector<vector<int>> aidx(L), bidx(L);
    for (int i = 0; i < n; ++i) {
        aidx[a[i].first].emplace_back(i);
    }
    for (int i = 0; i < m; ++i) {
        bidx[b[i].first].emplace_back(i);
    }
    ST st_plus(L), st_minus(L);
    vector<int> ans(m, INF);
    for (int x = 0; x < L; ++x) {
        for (int i : aidx[x]) {
            auto [x1, y1] = a[i];
            st_minus.upd(y1, -y1 - x1);
            st_plus.upd(y1, y1 - x1);
        }
        for (int j : bidx[x]) {
            auto [x2, y2] = b[j];
            ans[j] = min({ans[j], x2 + y2 + st_minus.get(0, y2), x2 - y2 + st_plus.get(y2, L)});
        }
    }
    st_plus.clear();
    st_minus.clear();
    for (int x = L - 1; x >= 0; --x) {
        for (int i : aidx[x]) {
            auto [x1, y1] = a[i];
            st_minus.upd(y1, -y1 + x1);
            st_plus.upd(y1, y1 + x1);
        }
        for (int j : bidx[x]) {
            auto [x2, y2] = b[j];
            ans[j] = min({ans[j], -x2 + y2 + st_minus.get(0, y2), -x2 - y2 + st_plus.get(y2, L)});
        }
    }
    cout << *max_element(all(ans)) << '\n';
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
