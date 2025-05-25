#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define _GLIBCXX_DEBUG
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<string> field(n);
    for (auto& el : field) cin >> el;
    vector good(n, vector<bool>(n, false));
    good[0][0] = true;
    string output;
    output += field[0][0];
    for (int sum = 0; sum < n - 1 + n - 1; ++sum) {
        char best = 'Z';
        for (int i = max(0, sum - n + 1); i < n && i <= sum; ++i) {
            if (!good[i][sum - i]) continue;
            if (i + 1 < n) best = min(best, field[i + 1][sum - i]);
            if (sum - i + 1 < n) best = min(best, field[i][sum - i + 1]);
        }
        output += best;
        for (int i = max(0, sum - n + 1); i < n && i <= sum; ++i) {
            if (!good[i][sum - i]) continue;
            if (i + 1 < n && field[i + 1][sum - i] == best) good[i + 1][sum - i] = true;
            if (sum - i + 1 < n && field[i][sum - i + 1] == best) good[i][sum - i + 1] = true;
        }
    }
    cout << output << '\n';
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