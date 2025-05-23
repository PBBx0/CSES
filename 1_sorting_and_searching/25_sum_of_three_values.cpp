#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    map<int, int> s;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            auto iter = s.find(x - a[i] - a[j]);
            if (iter != s.end()) {
                cout << iter->second + 1 << ' ' << i + 1 << ' ' << j + 1 << '\n';
                return;
            }
        }
        s.emplace(a[i], i);
    }
    cout << "IMPOSSIBLE\n";
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