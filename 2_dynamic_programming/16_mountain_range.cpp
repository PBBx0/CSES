#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

struct seg {
    int l, r, val;
};

bool operator<(seg a, seg b) {
    return a.l < b.l;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    map<int, vector<int>> pos;
    for (int i = 0; i < n; ++i) pos[a[i]].emplace_back(i);
    vector<int> dp(n);
    set<seg> s;
    for (auto [x, p] : pos) {
        for (int i : p) {
            auto iter = s.lower_bound({i, -1, -1});
            if (iter != s.end() && iter->l == i + 1) {
                dp[i] = max(dp[i], iter->val);
            }
            if (iter != s.begin() && (--iter)->r == i) {
                dp[i] = max(dp[i], iter->val);
            }
            ++dp[i];
        }
        for (int i : p) {
            auto iter = s.lower_bound({i, -1, -1});
            int l = i, r = i + 1, val = dp[i];
            if (iter != s.end() && iter->l == r) {
                r = iter->r;
                val = max(val, iter->val);
                iter = s.erase(iter);
            }
            if (iter != s.begin() && (--iter)->r == i) {
                l = iter->l;
                val = max(val, iter->val);
                iter = s.erase(iter);
            }
            s.emplace_hint(iter, seg{l, r, val});
        }
    }
    cout << s.begin()->val << '\n';
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