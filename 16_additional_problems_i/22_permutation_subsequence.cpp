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

const int INF = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int& el : a) {
        cin >> el;
        --el;
    }
    for (int& el : b) {
        cin >> el;
        --el;
    }
    if (n < m) swap(n, m), swap(a, b);
    vector<int> rev(n);
    for (int i = 0; i < n; ++i) rev[a[i]] = i;
    for (int& el : b) el = rev[el];
    vector<int> dp(m + 1, INF);
    dp[0] = -INF;
    vector<vector<pair<int, int>>> history(m + 1, {{INF, -1}});
    history[0] = {{-INF, -1}};
    for (int i = 0; i < m; ++i) {
        int len = lower_bound(all(dp), b[i]) - dp.begin();
        dp[len] = b[i];
        history[len].emplace_back(b[i], sz(history[len - 1]) - 1);
    }
    int len = m;
    while (dp[len] == INF) --len;
    vector<int> seq;
    int cur = sz(history[len]) - 1;
    while (len > 0) {
        auto [el, pr] = history[len][cur];
        seq.emplace_back(el);
        cur = pr;
        --len;
    }
    reverse(all(seq));
    cout << sz(seq) << '\n';
    for (int el : seq) cout << a[el] + 1 << ' ';
    cout << '\n';
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
