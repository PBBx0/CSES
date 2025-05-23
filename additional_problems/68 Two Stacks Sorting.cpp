#include <bits/stdc++.h>
#define sz(n) (int)(n).size()

using namespace std;
const int INF = 1e9 + 1000 - 7;
const int N = 2e5 + 1, T = 1 << 18;
int mn[N], mx[N], a[N], col[N], used[N], ans[N];
int mnt[T + T], mxt[T + T];
vector<int> g[N], vtx[N];
void update(int v, int c) {
    mn[v] = mx[v] = col[v] = c;
    for (v = (v + T) >> 1; v > 0; v >>= 1) {
        mnt[v] = mn[mnt[v + v]] < mn[mnt[v + v + 1]] ? mnt[v + v] : mnt[v + v + 1];
        mxt[v] = mx[mxt[v + v]] > mx[mxt[v + v + 1]] ? mxt[v + v] : mxt[v + v + 1];
    }
}
int min_query(int l, int r) {
    int res = l;
    for (l += T, r += T; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (mn[res] > mn[mnt[l]]) res = mnt[l];
            l++;
        }
        if (r & 1) {
            --r;
            if (mn[res] > mn[mnt[r]]) res = mnt[r];
        }
    }
    return res;
}
int max_query(int l, int r) {
    int res = l;
    for (l += T, r += T; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (mx[res] < mx[mxt[l]]) res = mxt[l];
            l++;
        }
        if (r & 1) {
            --r;
            if (mx[res] < mx[mxt[r]]) res = mxt[r];
        }
    }
    return res;
}
void unite(int u, int v) {
    g[u].emplace_back(v);
    g[v].emplace_back(u);
    u = col[u], v = col[v];
    if (sz(vtx[v]) < sz(vtx[u])) swap(v, u);
    for (int el : vtx[u]) {
        vtx[v].emplace_back(el);
        col[el] = v;
        if (mn[el] != INF) update(el, v);
    }
    vector<int> empty;
    vtx[u].swap(empty);
}
void dfs(int v) {
    for (int to : g[v]) if (ans[to] == 0) {
            ans[to] = 3 - ans[v];
            dfs(to);
        }
}
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; --a[i];
        vtx[i].emplace_back(i);
    }
    iota(col, col + n, 0);
    fill(mn, mn + n, INF);
    fill(mx, mx + n, -INF);
    iota(mnt + T, mnt + T + T, 0);
    iota(mxt + T, mxt + T + T, 0);
    for (int v = T - 1; v > 0; --v) {
        mnt[v] = mn[mnt[v + v]] < mn[mnt[v + v + 1]] ? mnt[v + v] : mnt[v + v + 1];
        mxt[v] = mx[mxt[v + v]] > mx[mxt[v + v + 1]] ? mxt[v + v] : mxt[v + v + 1];
    }
    int mex = 0;
    for (int i = 0; i < n; ++i) {
        int el = a[i];
        update(el, col[el]);
        while (true) {
            int l = min_query(mex, el);
            int r = max_query(mex, el);
            if (mn[l] == INF) break;
            if (col[l] == col[el] && col[r] == col[el]) break;
            if (col[l] != col[el]) unite(l, el);
            if (col[r] != col[el]) unite(r, el);
        }
        used[el] = 1;
        while (used[mex]) ++mex;
    }
    for (int v = 0; v < n; ++v) if (ans[v] == 0) {
            ans[v] = 1;
            dfs(v);
        }


    vector<int> f = {INF}, s = {INF};
    int out[n];
    for (int i = 0; i < n; ++i) out[i] = ans[a[i]];
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (out[i] == 1) {
            f.emplace_back(a[i]);
        } else {
            s.emplace_back(a[i]);
        }

        while (f.back() == cur || s.back() == cur) {
            if (f.back() == cur) {
                f.pop_back();
            } else {
                s.pop_back();
            }
            cur++;
        }
    }
    if (cur != n) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < n; ++i) cout << out[i] << ' ';
        cout << '\n';
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
    solve();
    return 0;
}