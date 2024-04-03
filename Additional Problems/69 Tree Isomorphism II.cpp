#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
using ll = int64_t;
const int N = 2e5;
int top = 0;
vector<int> g[2][N];
unordered_set<ll> used;
map<vector<ll>, ll> h;
int sz[2][N], p[2][N];
ll dfs(int id, int v, int par) {
    vector<ll> cur;
    for (int to : g[id][v]) if (to != par) {
        cur.emplace_back(dfs(id, to, v));
    }
    sort(cur.begin(), cur.end());
    if (h.contains(cur)) return h[cur];
    ll x = 0;
    while (used.contains(x)) x = rnd();
    used.insert(x);
    return h[cur] = x;
}
int calc_sz(int id, int v, int par) {
    p[id][v] = par;
    sz[id][v] = 1;
    for (int to : g[id][v]) if (to != par) {
        sz[id][v] += calc_sz(id, to, v);
    }
    return sz[id][v];
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
    calc_sz(0, top, top), calc_sz(1, top, top);
    set<ll> fst;
    for (int v = top; v < top + n; ++v) {
        int mx = n - sz[0][v];
        for (int to : g[0][v]) if (to != p[0][v]) {
            mx = max(mx, sz[0][to]);
        }
        if (mx * 2 <= n) fst.insert(dfs(0, v, v));
    }
    bool res = false;
    for (int v = top; v < top + n; ++v) {
        int mx = n - sz[1][v];
        for (int to : g[1][v]) if (to != p[1][v]) {
                mx = max(mx, sz[1][to]);
            }
        if (mx * 2 <= n) res |= fst.contains(dfs(1, v, v));
    }
    cout << (res ? "YES" : "NO") << '\n';
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