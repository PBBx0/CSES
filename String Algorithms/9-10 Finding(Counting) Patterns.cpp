#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;
const int N = 1e6;
vector<int> g[N];
int dp[N], ans[N];
const int C = 26;
struct node {
    vector<int> idx;
    int nx[C], suff = -1;
    node() {
        fill(nx, nx + C, -1);
    }
};
vector<node> t(1);
void add_word(string & s, int id) {
    int v = 0;
    for (char ch : s) {
        int x = ch - 'a';
        if (t[v].nx[x] == -1) {
            t[v].nx[x] = sz(t);
            t.emplace_back();
        }
        v = t[v].nx[x];
    }
    t[v].idx.emplace_back(id);
}
void build_aho() {
    vector<pair<int, int>> q;
    for (int x = 0; x < C; ++x) {
        if (t[0].nx[x] == -1) {
            t[0].nx[x] = 0;
        } else {
            q.emplace_back(0, x);
        }
    }
    for (int st = 0; st < sz(q); ++st) {
        auto [par, x] = q[st];
        int a = t[par].nx[x];
        if (t[par].suff == -1) {
            t[a].suff = 0;
        } else {
            t[a].suff = t[t[par].suff].nx[x];
        }
        g[t[a].suff].emplace_back(a);
        for (int y = 0; y < C; ++y) {
            if (t[a].nx[y] == -1) {
                t[a].nx[y] = t[t[a].suff].nx[y];
            } else {
                q.emplace_back(a, y);
            }
        }
    }
}
int dfs(int v) {
    for (int to : g[v]) {
        dp[v] += dfs(to);
    }
    for (int id : t[v].idx) ans[id] = dp[v];
    return dp[v];
}
void solve() {
    string txt;
    int n;
    cin >> txt >> n;
    for (int i = 0; i < n; ++i) {
        string tmp;
        cin >> tmp;
        add_word(tmp, i);
    }
    build_aho();
    int v = 0;
    for (char ch : txt) {
        int x = ch - 'a';
        v = t[v].nx[x];
        dp[v]++;
    }
    dfs(0);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
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