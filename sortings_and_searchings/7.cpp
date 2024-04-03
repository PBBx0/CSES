#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    pair<int, int> pos = {-1, -1};
    for (int j = 0; j < n; ++j) {
        auto it = lower_bound(a.begin() + j + 1, a.end(), make_pair(x - a[j].first, 0));
        if (it != a.end() && it->first + a[j].first == x) {
            pos = make_pair(a[j].second, it->second);
        }
    }
    if (pos.first == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << pos.first + 1 << ' ' << pos.second + 1 << '\n';
    }
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