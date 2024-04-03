#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

const int C = 26;
struct node {
    int nx[C], first = -1, suff = -1, zsuff = -1;
    vector<int> idx;
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
            t[a].zsuff = t[t[a].suff].idx.empty() ? t[t[a].suff].zsuff : t[a].suff;
        }
        for (int y = 0; y < C; ++y) {
            if (t[a].nx[y] == -1) {
                t[a].nx[y] = t[t[a].suff].nx[y];
            } else {
                q.emplace_back(a, y);
            }
        }
    }
}

void solve() {
    string txt;
    int n;
    cin >> txt >> n;
    vector<int> ans(n, -1), len(n);
    for (int i = 0; i < n; ++i) {
        string cur;
        cin >> cur;
        len[i] = sz(cur);
        add_word(cur, i);
    }
    build_aho();
    int v = 0;
    for (int i = 0; i < sz(txt); ++i) {
        int x = txt[i] - 'a';
        v = t[v].nx[x];
        for (int u = v; u != -1 && t[u].first == -1; u = t[u].zsuff) {
            t[u].first = i;
            for (int id : t[u].idx) {
                ans[id] = i - len[id] + 2;
            }
        }
    }
    for (int el : ans) cout << el << ' ';
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