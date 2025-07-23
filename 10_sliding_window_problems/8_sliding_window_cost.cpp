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

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    set<pair<int, int>> lft, rgt;
    int half = k / 2;
    ll sml = 0, smr = 0;
    for (int i = 0; i < n; ++i) {
        rgt.emplace(a[i], i);
        smr += a[i];
        if (sz(rgt) > half) {
            auto pr = *rgt.begin();
            rgt.erase(rgt.begin());
            smr -= pr.first;
            sml += pr.first;
            lft.emplace(pr);
        }
        if (i >= k) {
            auto iter = lft.find({a[i - k], i - k});
            if (iter != lft.end()) {
                sml -= a[i - k];
                lft.erase(iter);
            }
            iter = rgt.find({a[i - k], i - k});
            if (iter != rgt.end()) {
                smr -= a[i - k];
                rgt.erase(iter);
            }
            while (sz(rgt) < half) {
                auto pr = *lft.rbegin();
                lft.erase(--lft.end());
                sml -= pr.first;
                smr += pr.first;
                rgt.emplace(pr);
            }
        }
        if (i >= k - 1) {
            ll val = lft.rbegin()->first;
            ll ans = val * sz(lft) - sml + smr - val * sz(rgt);
            cout << ans << ' ';
        }
    }
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
