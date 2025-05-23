#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<pair<int, int>> g[N], rg[N];
ll d1[N], d2[N], dp1[N], dp2[N];
int col[N];
const ll INF = 1e18, MOD = 1e9 + 1000 - 7;
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g[a].emplace_back(b, c);
        rg[b].emplace_back(a, c);
    }
    fill(d1, d1 + n, INF);
    d1[0] = 0;
    dp1[0] = 1;
    set<pair<ll, int>> s;
    s.emplace(0, 0);
    while (!s.empty()) {
        auto [cur_d, v] = *s.begin();
        s.erase(s.begin());
        if (col[v]) continue;
        col[v] = 1;
        for (auto [to, w] : g[v]) {
            if (d1[to] > cur_d + w) {
                d1[to] = cur_d + w;
                dp1[to] = dp1[v];
                s.emplace(d1[to], to);
            } else if (d1[to] == cur_d + w) {
                dp1[to] += dp1[v];
                dp1[to] %= MOD;
            }
        }
    }
    fill(d2, d2 + n, INF);
    d2[n - 1] = 0;
    dp2[n - 1] = 1;
    s.emplace(0, n - 1);
    while (!s.empty()) {
        auto [cur_d, v] = *s.begin();
        s.erase(s.begin());
        if (col[v] == 2) continue;
        col[v] = 2;
        for (auto [to, w] : rg[v]) {
            if (d2[to] > cur_d + w) {
                d2[to] = cur_d + w;
                dp2[to] = dp2[v];
                s.emplace(d2[to], to);
            } else if (d2[to] == cur_d + w) {
                dp2[to] += dp2[v];
                dp2[to] %= MOD;
            }
        }
    }
    set<int> ans;
    for (int v = 0; v < n; ++v) {
        if (dp1[v] * dp2[v] % MOD == dp2[0] && d1[v] + d2[v] == d2[0]) ans.insert(v);
    }
    cout << sz(ans) << '\n';
    for (int x : ans) cout << x + 1 << ' ';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}