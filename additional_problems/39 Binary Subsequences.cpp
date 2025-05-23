#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#pragma GCC optimize("O3")
using namespace std;

inline int len(int a, int b) {
    if (a < b) swap(a, b);
    int ans = 0;
    while (b > 1) {
        ans += a / b;
        a %= b;
        swap(a, b);
    }
    return ans + a - b;
}
void solve() {
    int n;
    cin >> n;
    n++;
    int a = 1, l = n;
    for (int i = 1; i < n; ++i) {
        if (gcd(i, n + 1) == 1) {
            int l2 = len(i, n + 1 - i);
            if (l2 < l) {
                a = i, l = l2;
            }
        }
    }
    string out;
    int b = n + 1 - a;
    while (a > 1 || b > 1) {
        if (a > b) {
            out += '0';
            a -= b;
        } else {
            out += '1';
            b -= a;
        }
    }
    cout << out << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    solve();
    return 0;
}