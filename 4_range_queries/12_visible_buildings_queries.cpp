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

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<array<int, 3>> queries(q);
    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][0] >> queries[i][1];
        queries[i][2] = i;
        --queries[i][0];
    }
    sort(all(queries));
    vector<int> st;
    for (int pos = n - 1; pos >= 0; --pos) {
        while (!st.empty() && a[st.back()] <= a[pos]) st.pop_back();
        st.emplace_back(pos);
        while (!queries.empty() && queries.back()[0] == pos) {
            auto [l, r, i] = queries.back();
            queries.pop_back();
            ans[i] = lower_bound(rall(st), r) - st.rbegin();
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
