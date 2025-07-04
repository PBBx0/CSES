#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int MOD = 1e9 + 7;
const ll INF = 1e18;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

vector<vector<int>> g;
vector<int> dp_mn, dp_mx, dp_cnt;
vector<int> col;


void dfs(int v) {
    col[v] = 0;
    for (int to : g[v]) {
        if (col[to] == -1) dfs(to);
        if (col[to] == 0) continue;
        col[v] = 1;
        dp_mn[v] = min(dp_mn[v], 1 + dp_mn[to]);
        dp_mx[v] = max(dp_mx[v], 1 + dp_mx[to]);
        dp_cnt[v] = add(dp_cnt[v], dp_cnt[to]);
    }

}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> g0(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        g0[a].emplace_back(b, c);
    }
    vector<ll> dst(n, INF);
    vector<bool> used(n, false);
    dst[0] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [dv, v] = pq.top();
        pq.pop();
        if (used[v]) continue;
        used[v] = true;
        for (auto [to, w] : g0[v]) {
            if (dst[to] > dv + w) dst[to] = dv + w;
            pq.emplace(dv + w, to);
        }
    }
    cout << dst[n - 1] << ' ';
    g.resize(n);
    for (int v = 0; v < n; ++v) for (auto [to, w] : g0[v]) {
        if (dst[v] + w == dst[to]) g[v].emplace_back(to);
    }
    dp_cnt.resize(n, 0);
    dp_cnt[n - 1] = 1;
    dp_mn.resize(n, 1e9);
    dp_mn[n - 1] = 0;
    dp_mx.resize(n, 0);
    dp_mx[n - 1] = 0;
    col.resize(n, -1);
    col[n - 1] = 1;
    dfs(0);
    cout << dp_cnt[0] << ' ' << dp_mn[0] << ' ' << dp_mx[0] << '\n';
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