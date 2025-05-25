#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    sort(all(a));
    int sum = std::accumulate(all(a), 0);
    vector<bool> can(sum + 1);
    can[0] = true;
    for (int d : a) {
        for (int w = sum; w >= d; --w) {
            if (can[w - d]) can[w] = true;
        }
    }
    vector<int> output;
    for (int i = 1; i <= sum; ++i) if (can[i]) output.emplace_back(i);
    cout << sz(output) << '\n';
    for (int el : output) cout << el << ' ';
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