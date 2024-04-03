#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
ll ans = 0, k;
const int N = 2e5;
vector<int> g[N];
deque<int> dp[N];
void merge(deque<int> & a, deque<int> & b) {
    if (sz(a) < sz(b)) swap(a, b);
    for (int i = 0; i < sz(b); ++i) {
        if (k - (sz(b) - i) > 0 && k - (sz(b) - i) <= sz(a)) ans += 1LL * b[i] * a[sz(a) - (k - (sz(b) - i))];
    }
    for (int i = 1; i <= sz(b); ++i) a[sz(a)-i] += b[sz(b)-i];
}
void dfs(int v, int p) {
    for (int to : g[v]) if (to != p) {
            dfs(to, v);
            merge(dp[v], dp[to]);
        }
    dp[v].push_back(1);
    if (k < sz(dp[v])) ans += dp[v][sz(dp[v]) - k - 1];
}
void solve() {
    int n;
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
    cout << ans << '\n';
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