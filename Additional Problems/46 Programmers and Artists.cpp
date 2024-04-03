//shorturl.at/cdprV
#include <bits/stdc++.h>
#define sz(n) (ll)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    ll a, b, n;
    cin >> a >> b >> n;
    pair<ll, ll> p[n];
    for (auto & [x, y] : p) cin >> x >> y;
    sort(p, p + n);
    auto cmp1 = [](auto fst, auto snd) {
        return fst.first - fst.second > snd.first - snd.second;
    };
    auto cmp2 = [](auto fst, auto snd) {
        if (fst.second != snd.second) return fst.second > snd.second;
        return fst.first > snd.first;
    };
    multiset<pair<ll, ll>, decltype(cmp1)> fst, snd;
    multiset<pair<ll, ll>, decltype(cmp2)> s;
    ll ans = 0;
    for (auto [x, y] : p) fst.emplace(x, y), ans += x;
    ll c = n - a - b;
    int i = 0;
    for (;i < c; ++i) {
        s.insert(p[i]);
        fst.erase(fst.find(p[i]));
        ans -= p[i].first;
    }
    while (sz(fst) > a) {
        auto [x, y] = *fst.rbegin();
        fst.erase(--fst.end());
        ans += y - x;
        snd.emplace(x, y);
    }
    ll res = ans;
    for (; i < n; ++i) {
        if (fst.contains(p[i])) fst.erase(fst.find(p[i])), ans -= p[i].first;
        else snd.erase(snd.find(p[i])), ans -= p[i].second;
        s.insert(p[i]);
        auto p2 = *s.begin();
        s.erase(s.begin());
        if (fst.lower_bound(p2) == fst.end()) {
            snd.insert(p2);
            ans += p2.second;
        }  else {
            fst.insert(p2);
            ans += p2.first;
        }
        while (sz(fst) > a) {
            auto [x, y] = *fst.rbegin();
            fst.erase(--fst.end());
            ans += y - x;
            snd.emplace(x, y);
        }
        while (sz(snd) > b) {
            auto [x, y] = *snd.begin();
            snd.erase(snd.begin());
            ans += x - y;
            fst.emplace(x, y);
        }
        res = max(res, ans);
    }
    cout << res << '\n';
}

signed main() {
    ll tt = 1;
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    cin >> tt;
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    while (tt--) solve();
    return 0;
}