#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    multiset<int> tickets(all(a));
    for (int i = 0; i < m; ++i) {
        int p;
        cin >> p;
        auto iter = tickets.upper_bound(p);
        if (iter == tickets.begin()) {
            cout << -1 << '\n';
            continue;
        }
        --iter;
        cout << *iter << '\n';
        tickets.erase(iter);
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