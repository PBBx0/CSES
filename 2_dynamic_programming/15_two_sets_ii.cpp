#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int MOD = 1e9 + 7;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

void solve() {
    int n;
    cin >> n;
    int sum = n * (n + 1) / 2;
    if (sum & 1) {
        cout << 0 << '\n';
        return;
    }
    vector<int> cnt(sum / 2 + 1);
    cnt[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int w = sum / 2; w - i >= 0; --w) {
            cnt[w] = add(cnt[w], cnt[w - i]);
        }
    }
    cout << cnt[sum / 2] * 1LL * (MOD + 1) / 2 % MOD << '\n';
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