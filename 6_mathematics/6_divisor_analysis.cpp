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

const int MOD = 1e9 + 7;

int add (int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

int mul(int a, int b, int mod = MOD) {
    return 1LL * a * b % mod;
}

int binpow(int x, int pw) {
    int rs = 1;
    for (; pw > 0; pw >>= 1, x = mul(x, x)) if (pw & 1) rs = mul(rs, x);
    return rs;
}

int inv(int x) {
    return binpow(x, MOD - 2);
}

void solve() {
    int n;
    cin >> n;
    int cnt = 1, sum = 1;
    int cnt2 = 1, cnt3 = 1;
    bool square = true, first = true;
    int x = 1, x2 = 1;
    for (int i = 0; i < n; ++i) {
        int p, k;
        cin >> p >> k;
        cnt = mul(cnt, k + 1);
        sum = mul(sum, mul(add(MOD - 1, binpow(p, k + 1)), inv(add(MOD - 1, p))));

        x = mul(x, binpow(p, k));
        x2 = mul(x2, binpow(p, k / 2));

        square &= k % 2 == 0;
        cnt2 = mul(cnt2, k + 1, MOD - 1);
        if (k % 2 == 1 && first) {
            first = false;
            cnt3 = mul(cnt3, (k + 1) / 2, MOD - 1);
        } else {
            cnt3 = mul(cnt3, k + 1, MOD - 1);
        }

    }
    cout << cnt << ' ' << sum << ' ';
    if (square) {
        cout << binpow(x2, cnt2) << '\n';
    } else {
        cout << binpow(x, cnt3) << '\n';
    }
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
