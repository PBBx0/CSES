#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N];
int sz[N];
ll sum[N];
void dfs(int v, int par) {
    sz[v] = 1;
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
        sz[v] += sz[to];
        sum[v] += sum[to] + sz[to];
    }
}
int n;
void dfs2(int v, int par, ll top) {
    sum[v] += top;
    for (int to : g[v]) if (to != par) {
        dfs2(to, v, sum[v] - sum[to] - sz[to] + n - sz[to]);
    }
}
void solve() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, -1);
    dfs2(0, -1, 0);
    for (int i = 0; i < n; ++i) cout << sum[i] << ' ';
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