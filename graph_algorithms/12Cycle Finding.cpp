#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2500, M = 5000;
struct edge {
    int from, to;
    ll w;
    edge(int from = 0, int to = 0, ll w = 0) : from(from), to(to), w(w) {}
};
edge E[M];
ll d[N];
int par[N];
void solve() {
    int n, m;
    cin >> n >> m;
    fill(par, par + n, -1);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        E[i] = {a, b, w};
    }
    int iter = -1, vtx;
    for (int it = 0; it <= n; ++it) {
        for (int i = 0; i < m; ++i) {
            auto [v, to, w] = E[i];
            if (d[to] > d[v] + w) {
                d[to] = d[v] + w;
                par[to] = v;
                iter = it;
                vtx = v;
            }
        }
    }
    if (iter < n) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n';
    vector<int> used(n);
    for (; !used[vtx]; vtx = par[vtx]) {
        used[vtx] = true;
    }
    vector<int> out{vtx};
    for (int v = par[vtx]; v != vtx; v = par[v]) {
        out.emplace_back(v);
    }
    out.emplace_back(vtx);
    reverse(out.begin(), out.end());
    for (auto el : out) cout << el + 1 << ' ';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}