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

const int MOD = 1e9 + 7;
int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> r(n);
    set<int> s;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        while (cur < n && !s.contains(a[cur])) {
            s.emplace(a[cur]);
            ++cur;
        }
        r[i] = cur;
        s.erase(a[i]);
    }
    int boost = 1;
    vector<int> sub(n + 1);
    sub[0] = 1;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i <= n; ++i) {
        dp[i] = boost;
        if (i < n) {
            int j = r[i];
            boost = add(boost, dp[i]);
            sub[j] = add(sub[j], dp[i]);
        }
        boost = add(boost, MOD - sub[i]);

    }
    cout << dp[n] << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
