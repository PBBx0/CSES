#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5 + 3;
int dsu[N];
vector<tuple<int, int, int>> chs;
int get(int v) {
    return dsu[v] < 0 ? v : get(dsu[v]);
}
int cc;
void unite(int a, int b) {
    a = get(a), b = get(b);
    chs.emplace_back(a, dsu[a], 0);
    chs.emplace_back(b, dsu[b], a != b);
    if (a == b) return;
    cc--;
    if (dsu[a] > dsu[b]) swap(a, b);
    dsu[a] += dsu[b];
    dsu[b] = a;
}
void rollback(int k) {
    for (int i = 0; i < k * 2; ++i) {
        auto [p, v, x] = chs.back();
        cc += x;
        dsu[p] = v;
        chs.pop_back();
    }
}
pair<int, int> E[N + N];
const int M = 1 << 18;
vector<int> t[M << 1];
void update(int l, int r, int x) {
    for (l += M, r += M; l < r; l >>= 1, r >>= 1) {
        if (l & 1) t[l++].emplace_back(x);
        if (r & 1) t[--r].emplace_back(x);
    }
}
int n, m, q;
void process(int v, int tl, int tr) {
    for (int id : t[v]) {
        auto [a, b] = E[id];
        unite(a, b);
    }
    if (tl + 1 == tr) {
        if (tl <= q) cout << cc << ' ';
    } else {
        int tm = (tr - tl) / 2 + tl;
        process(v + v, tl, tm);
        process(v + v + 1, tm, tr);
    }
    rollback(sz(t[v]));
}
void solve() {
    cin >> n >> m >> q;
    map<pair<int, int>, int> idx, tm;
    cc = n;
    fill(dsu, dsu + n, -1);
    int c = 0;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        auto p = minmax(a, b);
        if (!idx.contains(p)) {
            idx[p] = c;
            tm[p] = 0;
            E[c++] = p;
        }
    }
    for (int i = 0; i < q; ++i) {
        int tp, a, b;
        cin >> tp >> a >> b;
        a--, b--;
        auto p = minmax(a, b);
        if (!idx.contains(p)) {
            idx[p] = c;
            E[c++] = p;
        }
        if (tp == 1) {
            tm[p] = i + 1;
        } else {
            update(tm[p], i + 1, idx[p]);
            tm[p] = -1;
        }
    }
    for (int i = 0; i < c; ++i) if (tm[E[i]] != -1) {
        update(tm[E[i]], M, i);
    }
    process(1, 0, M);
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