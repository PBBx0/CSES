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

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
