#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

const int N = 1e4 + 1;
//int dp[N];
void solve() {
    set<int> zeros{
            0, 1, 2, 4, 7, 10, 20, 23, 26, 50, 53, 270, 273, 276,
            282, 285, 288, 316, 334, 337, 340, 346, 359, 362, 365,
            386, 389, 392, 566, 630, 633, 636, 639, 673, 676, 682,
            685, 923, 926, 929, 932, 1222,
    };
/*    for (int x = 0; x < N; ++x) {
        vector<int> t;
        for (int d = 1; d * 2 < x; ++d) {
            t.emplace_back(dp[d] ^ dp[x - d]);
        }
        vector<bool> used(sz(t) + 1, false);
        for (int el : t) {
            used[el] = true;
        }
        int ptr = 0;
        while (used[ptr]) ptr++;
        dp[x] = ptr;
        if (!dp[x]) zeros.insert(x);
    }
    for (auto el : zeros) cerr << el << ", ";*/
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << (zeros.count(n) ? "second" : "first") << '\n';
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
    solve();
    return 0;
}