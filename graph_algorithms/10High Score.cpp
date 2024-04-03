#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
using ll = int64_t;
const int N = 2500, M = 5000;
const ll INF = 1e15;
ll d[N];
struct edge {
    int from, to;
    ll w;
    edge(int from = 0, int to = 0, int w = 0) : from(from), to(to), w(w) {}
};
edge E[M];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        E[i] = {a, b, c};
    }
    fill(d, d + n, -INF);
    d[0] = 0;
    vector<bool> in_cycle(n), can_access(n), could(n);
    could[0] = true;
    can_access[n - 1] = true;
    for (int it = 0; it < n; ++it) {
        for (int i = 0; i < m; ++i) {
            auto [v, to, w] = E[i];
            if (d[to] < d[v] + w) {
                d[to] = d[v] + w;
            }
            if (can_access[to]) can_access[v] = true;
            if (could[v]) could[to] = true;
        }
    }
    for (int it = 0; it < n; ++it) {
        for (int i = 0; i < m; ++i) {
            auto [v, to, w] = E[i];
            if (d[to] < d[v] + w) {
                d[to] = d[v] + w;
                in_cycle[to] = true;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (could[i] && can_access[i] && in_cycle[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << d[n - 1] << '\n';
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