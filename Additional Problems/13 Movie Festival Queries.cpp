#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int LOG = 20;
const int N = 2e6 + 1;
void solve() {
    int n, q;
    cin >> n >> q;
    pair<int, int> mv[n];
    int fst[N], nxt[n], up[LOG][n];
    fill(fst, fst + N, -1);
    fill(nxt, nxt + n, -1);
    for (auto & [l, r] : mv) {
        cin >> l >> r;
    }
    sort(mv, mv + n);
    vector<pair<int, int>> ev;
    for (int i = 1; i <= n; ++i) {
        ev.emplace_back(mv[i - 1].first, i);
        ev.emplace_back(mv[i - 1].second, -i);
    }
    sort(ev.begin(), ev.end(), [](auto fst, auto snd) {
        if (fst.first != snd.first)
            return fst.first < snd.first;
        return fst.second < snd.second;
    });
    set<tuple<int, int, int>> s;
    for (int i = 0; i < n; ++i) {
        s.emplace(mv[i].second, mv[i].first, i);
    }
    for (auto [x, id] : ev) {
        if (id < 0) {
            if (!s.empty()) {
                auto [l, r, id2] = *s.begin();
                nxt[-id - 1] = id2;
            }
        } else {
            s.erase({mv[id - 1].second, mv[id - 1].first, id - 1});
        }
    }
    s.clear();
    for (int i = 0; i < n; ++i) {
        s.emplace(mv[i].second, mv[i].first, i);
    }
    int p = 0;
    for (int l = 0; l < N; ++l) {
        while (p < n && mv[p].first < l) {
            s.erase({mv[p].second, mv[p].first, p});
            p++;
        }
        if (!s.empty()) {
            auto [r1, l1, id] = *s.begin();
            fst[l] = id;
        }
    }
    for (int i = 0; i < n; ++i) up[0][i] = nxt[i];
    for (int l = 1; l < LOG; ++l) {
        for (int i = 0; i < n; ++i) {
            up[l][i] = up[l - 1][i] == -1 ? -1 : up[l - 1][up[l - 1][i]];
        }
    }
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        int v = fst[l];
        if (v == -1 || mv[v].second > r) {
            cout << 0 << '\n';
            continue;
        }
        int res = 1;
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[j][v] != -1 && mv[up[j][v]].second <= r) {
                v = up[j][v];
                res += (1 << j);
            }
        }
        cout << res << '\n';
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