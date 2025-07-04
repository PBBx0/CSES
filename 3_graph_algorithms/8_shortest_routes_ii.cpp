#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const ll INF = 1e18;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> dst(n, vector<ll>(n, INF));
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        --a, --b;
        dst[a][b] = min(dst[a][b], c);
        dst[b][a] = min(dst[b][a], c);
    }
    for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
        dst[k][k] = 0;
    }
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        cout << (dst[a][b] == INF ? -1 : dst[a][b]) << '\n';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}