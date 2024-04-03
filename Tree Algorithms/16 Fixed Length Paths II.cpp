#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
ll ans = 0;
int lo = 0, hi = 0;
const int N = 2e5;
int t[N];
inline int get(int p) {
    int res = 0;
    for (; p > 0; p &= p - 1) res += t[p - 1];
    return res;
}
inline int get(int l, int r) {
    return get(r) - get(l);
}
inline void update(int p, int x) {
    for (; p < N; p |= p + 1) t[p] += x;
}
vector<int> g[N], vts;
int sz[N], level[N];
int calc_sz(int v, int par) {
    sz[v] = 1;
    for (int to : g[v]) if (level[to] == -1 && to != par) {
            sz[v] += calc_sz(to, v);
        }
    vts.emplace_back(v);
    return sz[v];
}

void dfs(int v, int par, int cur_dist, vector<int> & cnt) {
    cnt[cur_dist]++;
    for (int to : g[v]) if (level[to] == -1 && to != par) {
        dfs(to, v, cur_dist + 1, cnt);
    }
}

void find_centroid(int v, int lvl) {
    vts.clear();
    int all_sz = calc_sz(v, v);
    for (int el : vts) {
        if (sz[el] * 2 >= all_sz) {
            v = el;
            break;
        }
    }
    vector<int> cnt(sz[v] + 1), cur(sz[v] + 1);
    level[v] = lvl;
    update(0, 1);
    for (int to : g[v]) if (level[to] == -1) {
        dfs(to, v, 1, cur);
        for (int i = 0; i <= sz[to] && i < sz(cur); ++i) {
            ans += get(max(0, lo - i), max(0, hi - i)) * cur[i];
            cnt[i] += cur[i];
        }
        for (int i = 0; i <= sz[to] && i < sz(cur); ++i) {
            update(i, cur[i]);
            cur[i] = 0;
        }
    }
    update(0, -1);
    for (int i = 0; i <= sz[v]; ++i) {
        update(i, -cnt[i]);
    }
    for (int to : g[v]) if (level[to] == -1) {
        find_centroid(to, lvl + 1);
    }
}

void solve() {
    fill(level, level + N, -1);
    int n;
    cin >> n >> lo >> hi;
    hi++;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    find_centroid(0, 0);
    cout << ans << '\n';
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
