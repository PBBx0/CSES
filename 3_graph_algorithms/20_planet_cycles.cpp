#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int LOG = 20;

void solve() {
    int n;
    cin >> n;
    vector<int> f(n);
    for (int& el : f) {
        cin >> el;
        --el;
    }

    vector bj(LOG, vector<int>(n));
    bj[0] = f;
    for (int l = 1; l < LOG; ++l) {
        for (int v = 0; v < n; ++v) {
            bj[l][v] = bj[l - 1][bj[l - 1][v]];
        }
    }

    vector<int> color(n, -2), cycle_len;
    vector<int> cycle_pos(n), height(n);
    int c = -1;
    for (int v = 0; v < n; ++v) {
        if (color[v] != -2) continue;
        int u = v;
        int iter = 0, len = 0;
        for (; color[u] == -2; u = f[u]) {
            color[u] = -1;
            ++iter;
        }
        if (color[u] == -1) {
            ++c;
            for (int t = u; color[t] == -1; t = f[t]) {
                color[t] = c;
                height[t] = 0;
                cycle_pos[t] = len++;
            }
            cycle_len.emplace_back(len);
        }

        for (int t = v; color[t] == -1; t = f[t]) {
            color[t] = color[u];
            cycle_pos[t] = -1;
            height[t] = iter - len + height[u];
            --iter;
        }
    }

    for (int v = 0; v < n; ++v) {
        cout << height[v] + cycle_len[color[v]] << ' ';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}