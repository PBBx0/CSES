#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    int ar[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char t;
            cin >> t;
            ar[i][j] = t == '.' ? 1 : 0;
        }
    }
    int dp[m];
    int lt[m], rt[m];
    vector<int> st;
    fill(dp, dp + m, 0);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) dp[j] = ar[i][j] ? dp[j] + 1 : 0;
        st.clear();
        fill(lt, lt + m, -1);
        fill(rt, rt + m, m);
        for (int j = 0; j < m; ++j) {
            while (!st.empty() && dp[st.back()] > dp[j]) {
                rt[st.back()] = j;
                st.pop_back();
            }
            if (!st.empty()) {
                lt[j] = dp[st.back()] == dp[j] ? lt[st.back()] : st.back();
            }
            st.emplace_back(j);
        }
        for (int j = 0; j < m; ++j) {
            res = max(res, dp[j] * (rt[j] - lt[j] - 1));
        }
    }
    cout << res << '\n';
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