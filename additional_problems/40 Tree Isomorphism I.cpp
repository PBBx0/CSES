#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int N = 2e5;
vector<int> g[2][N];
map<vector<ll>, ll> h;
unordered_set<ll> used;
int top = 0;
ll dfs(int id, int v, int par) {
    vector<ll> cur;
    for (int to : g[id][v]) if (to != par) {
        cur.emplace_back(dfs(id, to, v));
    }
    sort(cur.begin(), cur.end());
    if (h.contains(cur)) {
        return h[cur];
    }
    ll x = 0;
    while (used.contains(x)) x = rnd();
    used.insert(x);
    h[cur] = x;
    return x;
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a += top - 1, b += top - 1;
        g[0][a].emplace_back(b);
        g[0][b].emplace_back(a);
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a += top - 1, b += top - 1;
        g[1][a].emplace_back(b);
        g[1][b].emplace_back(a);
    }
    h.clear();
    used.clear();
    ll h1 = dfs(0, top, top);
    ll h2 = dfs(1, top, top);
    cout << (h1 == h2 ? "YES" : "NO") << '\n';
    top += n;
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}