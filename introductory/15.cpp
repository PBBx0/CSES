#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    vector<string> out;
    do {
        out.emplace_back(s);
    } while (next_permutation(s.begin(), s.end()));
    cout << sz(out) << '\n';
    for (const auto& el : out) cout << el << '\n';
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