#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const ll INF = 1e18;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, ll>>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        g[a].emplace_back(b, c);
    }
    vector<int> cnt(n);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.emplace(0, 0);
    vector<ll> ans(k, INF);
    while (!pq.empty()) {
        auto [dv, v] = pq.top();
        pq.pop();
        if (cnt[v] >= k) continue;
        if (v == n - 1) ans[cnt[v]] = dv;
        ++cnt[v];
        for (auto [to, w] : g[v]) {
            if (cnt[to] < k) pq.emplace(dv + w, to);
        }
    }
    for (int i = 0; i < k; ++i) cout << ans[i] << ' ';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}