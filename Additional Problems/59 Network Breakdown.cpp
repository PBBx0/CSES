#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
int dsu[N];
int get(int v) {
    return dsu[v] < 0 ? v : dsu[v] = get(dsu[v]);
}
bool unite(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) return false;
    if (dsu[a] > dsu[b]) swap(a, b);
    dsu[a] += dsu[b];
    dsu[b] = a;
    return true;
}
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    fill(dsu, dsu + n, -1);
    int ans[k];
    set<pair<int, int>> all;
    vector<pair<int, int>> e(k);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a > b) swap(a, b);
        all.emplace(a, b);
    }
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a > b) swap(a, b);
        all.erase({a, b});
        e[i] = {a, b};
    }
    int cur = n;
    for (auto [a, b] : all) cur -= unite(a, b);
    for (int j = k - 1; j >= 0; --j) {
        ans[j] = cur;
        auto [a, b] = e[j];
        cur -= unite(a, b);
    }
    for (int el : ans) cout << el << ' ';
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