#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
const ll MOD = 1e9 + 7;
vector<int> g[N];
int col[N];
void dfs(int v) {
    col[v] = 1;
    for (int to : g[v]) if (col[to] == 0) dfs(to);
}
ll pw(ll a, ll pw) {
    ll res = 1;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    int c = 0;
    for (int v = 0; v < n; ++v) {
        if (col[v] == 0) dfs(v), c++;
    }
    cout << pw(2, m - n + c) << '\n';
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