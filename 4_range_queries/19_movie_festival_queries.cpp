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

const int LOG = 19;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> m(n);
    vector<array<int, 3>> queries(q);
    vector<int> ans(q);
    for (auto& [l, r] : m) cin >> l >> r;
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][0] >> queries[i][1];
        queries[i][2] = i;
    }
    m.emplace_back(-2, -1);
    sort(all(m));
    vector<pair<int, int>> right(n + 1);
    for (int i = 0; i <= n; ++i) right[i] = {m[i].second, i};
    sort(all(right));
    sort(all(queries));
    vector bj(LOG, vector<int>(n + 1));
    set<pair<int, int>> s;
    for (int i = n; i >= 0; --i) {
        auto [l, r] = m[i];
        while (!queries.empty() && queries.back()[0] > l) {
            auto [a, b, id] = queries.back();
            queries.pop_back();
            if (s.empty()) {
                ans[id] = 0;
                continue;
            }
            auto [_, j] = *s.begin();
            if (m[j].second > b) {
                ans[id] = 0;
                continue;
            }
            ans[id] = 1;
            for (int lvl = LOG - 1; lvl >= 0; --lvl) {
                if (bj[lvl][j] == -1) continue;
                if (m[bj[lvl][j]].second <= b) {
                    j = bj[lvl][j];
                    ans[id] += 1 << lvl;
                }
            }
        }

        while (!right.empty() && right.back().first > l) {
            auto [a, id] = right.back();
            right.pop_back();
            if (s.empty()) {
                bj[0][id] = -1;
            } else {
                auto [_, j] = *s.begin();
                bj[0][id] = j;
            }
            for (int lvl = 1; lvl < LOG; ++lvl) {
                bj[lvl][id] = bj[lvl - 1][id] == -1 ? -1 : bj[lvl - 1][bj[lvl - 1][id]];
            }
        }

        s.emplace(r, i);
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
