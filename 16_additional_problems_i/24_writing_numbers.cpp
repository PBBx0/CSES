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

ll count(ll x) {
    ll res = 0;
    for (; x > 0; x /= 10) res += x % 10 == 1;
    return res;
}

void solve() {
    ll n;
    cin >> n;
    ll on = 0;
    ll cnt = 0, x = 0;
    ll ten = 1e18;
    for (int i = 18; i > 2; --i, ten /= 10) {
        ll cur = ten / 10 * (i + 10 * on);
        if (cnt + cur <= n) {
            cnt += cur;
            x += ten;
            on++;
        }
        cur = ten / 10 * (i + 10 * on);
        if (cnt + cur <= n) {
            cnt += cur;
            x += ten;
            on--;
        }
        cur = ten / 10 * (i + 10 * on);
        while (cnt + cur <= n) {
            cnt += cur;
            x += ten;
        }
    }
    if (x > 0) x--;
    while (x > 0 && !count(x)) x--;
    while (cnt + count(x + 1) <= n) {
        ++x;
        cnt += count(x);
    }
    cout << x << '\n';
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
