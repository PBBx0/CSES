#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
int nx[N], sz[N + 1], col[N], h[N], comp[N];
int count_h(int v) {
    if (h[v] != -1) return h[v];
    if (col[v] == 2) return h[v] = 0;
    h[v] = count_h(nx[v]) + 1;
    comp[v] = comp[nx[v]];
    return h[v];
}
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> nx[i];
        nx[i]--;
    }
    fill(h, h + n, -1);
    int c = 0;
    for (int v = 0; v < n; ++v) if (col[v] == 0) {
        int t = v;
        for (; col[t] == 0; t = nx[t]) {
            col[t] = 3;
        }
        if (col[t] == 3) {
            col[t] = 2;
            comp[t] = ++c;
            sz[c]++;
            for (int y = nx[t]; y != t; y = nx[y]) {
                col[y] = 2;
                comp[y] = c;
                sz[c]++;
            }
        }
        for (int y = v; col[y] == 3; y = nx[y]) {
            col[y] = 1;
        }
    }
    for (int v = 0; v < n; ++v) if (h[v] == -1) {
        count_h(v);
    }
    for (int v = 0; v < n; ++v) {
        cout << h[v] + sz[comp[v]] << ' ';
    }
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