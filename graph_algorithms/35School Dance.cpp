#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 500;
int mt[N], col[N];
vector<int> g[N];
bool kuhn(int v, int c) {
    if (col[v] == c) return false;
    col[v] = c;
    for (int to : g[v]) {
        if (mt[to] == -1) {
            return mt[to] = v, true;
        }
    }
    for (int to : g[v]) {
        if (kuhn(mt[to], c)) {
            return mt[to] = v, true;
        }
    }
    return false;
}
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
    }
    fill(mt, mt + m, -1);
    int res = 0;
    for (int v = 0; v < n; ++v) {
        res += kuhn(v, v + 1);
    }
    cout << res << '\n';
    for (int i = 0; i < m; ++i) if (mt[i] != -1) {
        cout << mt[i] + 1 << ' ' << i + 1 << '\n';
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