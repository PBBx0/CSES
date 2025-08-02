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

struct FT {
    vector<int> t;

    FT(int n) : t(n) {}

    int get(int p) {
        int r = 0;
        for (; p > 0; p &= p - 1) r += t[p - 1];
        return r;
    }

    void upd(int p, int x) {
        for (; p < sz(t); p |= p + 1) t[p] += x;
    }
};

const int INF = 1e9;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int& el : p) {
        cin >> el;
        --el;
    }
    array<ll, 4> ans{};
    {
        FT ft(n);
        ll& cur_ans = ans[0];
        for (int i = 0; i < n; ++i) {
            cur_ans += i - ft.get(p[i]);
            ft.upd(p[i], 1);
        }
    }
    {
        vector<int> used(n);
        int c = 0;
        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            ++c;
            for (int j = i; !used[j]; j = p[j]) {
                used[j] = 1;
            }
        }
        ans[1] = n - c;
    }

    {
        vector<int> dp(n + 1, INF);
        dp[0] = -INF;
        for (int x : p) {
            *lower_bound(all(dp), x) = x;
        }
        int len = n;
        while (dp[len] == INF) --len;
        ans[2] = n - len;
    }

    {
        int last_pos = n;
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[p[i]] = i;
        int cnt = 0;
        for (int x = n - 1; x >= 0; --x) {
            if (pos[x] > last_pos) break;
            last_pos = pos[x];
            ++cnt;
        }
        ans[3] = n - cnt;
    }
    for (ll el : ans) cout << el << ' ';
    cout << '\n';

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
