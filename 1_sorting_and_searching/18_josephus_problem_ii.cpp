#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    ordered_set<int> a;
    for (int i = 1; i <= n; ++i) a.insert(i);
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        pos = (pos + k) % (n - i);
        auto iter = a.find_by_order(pos);
        cout << *iter << ' ';
        a.erase(iter);
    }
    cout << '\n';
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