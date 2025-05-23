#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N], vts;
int sz[N];
int calc_sz(int v, int par) {
    sz[v] = 1;
    for (int to : g[v]) if (to != par) {
        sz[v] += calc_sz(to, v);
    }
    vts.emplace_back(v);
    return sz[v];
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    int all_sz = calc_sz(0, 0);
    for (int el : vts) {
        if (sz[el] * 2 >= all_sz) {
            cout << el + 1 << '\n';
            return;
        }
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}