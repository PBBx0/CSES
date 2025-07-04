#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n), rg(n);
    vector<int> visited(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        rg[b].emplace_back(a);
    }
    const int REACHED = 1, R_REACHED = 2;
    deque<int> q{0};
    visited[0] = REACHED | R_REACHED;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int to : g[v]) {
            if ((visited[to] & REACHED) == 0) {
                visited[to] |= REACHED;
                q.emplace_back(to);
            }
        }
    }
    q.emplace_back(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int to : rg[v]) {
            if ((visited[to] & R_REACHED) == 0) {
                visited[to] |= R_REACHED;
                q.emplace_back(to);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if ((visited[i] & REACHED) == 0) {
            cout << "NO\n" << 1 << ' ' << i + 1 << '\n';
            return;
        }
        if ((visited[i] & R_REACHED) == 0) {
            cout << "NO\n" << i + 1 << ' ' << 1 << '\n';
            return;
        }
    }
    cout << "YES\n";
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