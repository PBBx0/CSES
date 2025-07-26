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

struct MegaSet {
    ll add = 0;
    set<pair<int, ll>> s;

    pair<int, ll> top() {
        auto [l, val] = *s.rbegin();
        return {l, val + add};
    }

    void pop() {
        s.erase(--s.end());
    }

    void emplace(int c, ll val) {
        s.emplace(c, val - add);
    }

    bool empty() {
        return sz(s) == 0;
    }

    void merge(MegaSet&& b) {
        if (sz(b.s) > sz(s)) swap(*this, b);
        ll delta = b.add - add;
        for (auto [l, c] : b.s) s.emplace(l, c + delta);
        b.s.clear();
    }

};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<MegaSet> A(n + 1);
    for (int i = 0; i < m; ++i) {
        int l, r;
        ll s;
        cin >> l >> r >> s;
        --l;
        A[r].emplace(l, s);
    }
    vector<pair<int, ll>> real(n + 1, {-1, 0});
    for (int r = n; r > 0; --r) {
        if (A[r].empty()) continue;
        auto [l, sm] = A[r].top();
        A[r].pop();
        while (!A[r].empty() && A[r].top().first == l) {
            if (A[r].top().second != sm) {
                cout << "NO\n";
                return;
            }
            A[r].pop();
        }
        real[r] = {l, sm};
        A[r].add -= sm;
        A[l].merge(std::move(A[r]));
    }
    vector<ll> pref(n + 1);
    vector<ll> ans(n);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i];
        auto [l, sm] = real[i + 1];
        if (l == -1) continue;
        ans[i] = sm - (pref[i + 1] - pref[l]);
        pref[i + 1] += ans[i];
    }

    cout << "YES\n";
    for (auto el : ans) cout << el << ' ';
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
