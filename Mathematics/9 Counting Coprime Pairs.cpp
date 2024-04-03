#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int T = 1e6 + 1;
int md[T], cnt[T];
vector<int> primes;
void solve() {
    primes.reserve(8e4);
    fill(md, md + T, -1);
    for (int i = 2; i < T; ++i) {
        if (md[i] == -1)
            primes.emplace_back(md[i] = i);
        for (int p : primes) {
            if (p > md[i] || p * i >= T) break;
            md[i * p] = p;
        }
    }
    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll& el : a) cin >> el;
    for (ll x : a) {
        vector<ll> pr;
        for (ll t = x; t > 1; t /= md[t])
            if (pr.empty() || md[t] != pr.back())
                pr.emplace_back(md[t]);
        ll k = sz(pr);
        for (ll mask = 1; mask < (1 << k); ++mask) {
            ll cur = 1;
            for (int i = 0; i < k; ++i) if (mask & (1 << i)) {
                cur *= pr[i];
            }
            cnt[cur]++;
        }
    }
    ll ans = 0;
    for (ll x : a) {
        vector<ll> pr;
        for (ll t = x; t > 1; t /= md[t])
            if (pr.empty() || md[t] != pr.back())
                pr.emplace_back(md[t]);
        ll k = sz(pr);
        ll res = n - 1;
        for (ll mask = 1; mask < (1 << k); ++mask) {
            ll cur = 1, cur_cnt = 0;
            for (int i = 0; i < k; ++i) if (mask & (1 << i)) {
                cur *= pr[i];
                cur_cnt++;
            }
            ll tmp = cnt[cur] - 1;
            if (cur_cnt & 1) tmp = -tmp;
            res += tmp;
        }
        ans += res;
    }
    cout << ans / 2 << '\n';
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