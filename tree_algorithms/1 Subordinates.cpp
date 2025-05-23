#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
int sz[N], par[N];
vector<int> g[N];
int calc_sz(int v) {
    sz[v] = 1;
    for (int to : g[v]) sz[v] += calc_sz(to);
    return sz[v];
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> par[i];
        par[i]--;
        g[par[i]].emplace_back(i);
    }
    calc_sz(0);
    for (int i = 0; i < n; ++i) cout << sz[i] - 1 << '\n';
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