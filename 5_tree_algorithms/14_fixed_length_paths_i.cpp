#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

vector<vector<int>> g;
int k;
ll ans = 0;

struct DP {
    vector<int> t;

    void emplace_front(int x) {
        t.emplace_back(x);
    }

    int& operator[](int i) {
        return t[sz(t) - i - 1];
    }

    int size() const {
        return sz(t);
    }

};

DP dfs(int v, int par) {
    DP cur;
    for (int to : g[v]) if (to != par) {
        auto dp = dfs(to, v);
        if (dp.size() > cur.size()) swap(dp, cur);
        for (int i = 0; i < dp.size(); ++i) {
            if (k - i - 2 >= 0 && k - i - 2 < cur.size()) ans += 1LL * dp[i] * cur[k - i - 2];
        }
        for (int i = 0; i < dp.size(); ++i) {
            cur[i] += dp[i];
        }
    }
    cur.emplace_front(1);
    if (k < cur.size()) ans += cur[k];
    return cur;
}

void solve() {
    int n;
    cin >> n >> k;
    g.resize(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
    cout << ans << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
