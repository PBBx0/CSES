#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ordered_set<pair<int, int>> s;
    for (int i = 0; i < n; ++i) {
        s.insert({a[i], i});
        if (i >= k) {
            s.erase({a[i - k], i - k});
        }
        if (i >= k - 1) {
            cout << s.find_by_order((k - 1) / 2)->first << '\n';
        }
    }
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
