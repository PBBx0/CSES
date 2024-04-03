#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
int dsu[N], ans[N];
vector<pair<int, int>> que[N];
int get(int v) {
    return dsu[v] < 0 ? v : dsu[v] = get(dsu[v]);
}
void unite(int a, int b, int i) {
    a = get(a), b = get(b);
    if (a == b) return;
    if (dsu[a] > dsu[b]) swap(a, b);
    for (auto [to, id] : que[b]) if (ans[id] == -1) {
        if (get(to) == a) {
            ans[id] = i + 1;
        } else {
            que[a].emplace_back(to, id);
        }
    }
    dsu[a] += dsu[b];
    dsu[b] = a;
    que[b].clear();
}
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<pair<int, int>> E(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        E[i] = {a, b};
    }
    fill(ans, ans + q, -1);
    fill(dsu, dsu + n, -1);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a == b) {
            ans[i] = 0;
        } else {
            que[a].emplace_back(b, i);
            que[b].emplace_back(a, i);
        }
    }
    for (int i = 0; i < m; ++i) {
        auto [a, b] = E[i];
        unite(a, b, i);
    }
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
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