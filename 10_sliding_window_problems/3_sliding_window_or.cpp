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
    ll x;
    int a, b, c;
    cin >> x >> a >> b >> c;

    deque<ll> arr{x};
    auto nxt = [a, b, c](ll x) {
        return (x * a + b) % c;
    };

    for (int i = 1; i < k; ++i) {
        arr.emplace_back(nxt(arr.back()));
    }
    ll cur = 0;

    deque<int> idx, idx2;
    for (int i = k - 1; i >= 0; --i) {
        if ((cur | arr[i]) != cur) {
            idx.emplace_back(i);
            cur |= arr[i];
        }
    }
    ll ans = 0;

    for (int i = 0; i <= n - k; ++i) {
        ans ^= cur;

        if (!idx.empty() && idx.back() == i) idx.pop_back();
//        cerr << sz(idx) << '\n';
        ll el = nxt(arr.back());
        arr.emplace_back(el);
        cur = 0;
        idx2.clear();
        if (el != 0) {
            cur |= el;
            idx2.emplace_back(i + k);
        }
        for (int j : idx) {
            if ((cur | arr[j - i]) != cur) {
                idx2.emplace_back(j);
                cur |= arr[j - i];
            }
        }
        idx = std::move(idx2);
        arr.pop_front();
    }
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
