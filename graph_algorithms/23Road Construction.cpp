#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
int mx = 1;
struct DSU {
    int par[N];
    DSU(int n) { fill(par, par + n, -1); }
    int get(int v) { return par[v] < 0 ? v : par[v] = get(par[v]); }
    bool merge(int a, int b) {
        a = get(a), b = get(b);
        if (a == b) return false;
        if (par[a] > par[b]) swap(a, b);
        par[a] += par[b];
        mx = max(mx, -par[a]);
        par[b] = a;
        return true;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    int cnt = n;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cnt -= dsu.merge(a, b);
        cout << cnt << ' ' << mx << '\n';
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