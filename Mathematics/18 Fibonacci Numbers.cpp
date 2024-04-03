#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
struct matrix {
    ll a = 1, b = 0, c = 0, d = 1;
    matrix(ll a = 1, ll b = 0, ll c = 0, ll d = 1) : a(a), b(b), c(c), d(d) {}
    void operator *= (const matrix & m) {
        ll na = (a * m.a % MOD + b * m.c % MOD) % MOD;
        ll nb = (a * m.b % MOD + b * m.d % MOD) % MOD;
        ll nc = (c * m.a % MOD + d * m.c % MOD) % MOD;
        ll nd = (c * m.b % MOD + d * m.d % MOD) % MOD;
        a = na, b = nb, c = nc, d = nd;
    }
    ll get() {
        return d;
    }
};
matrix pow(matrix a, ll pw) {
    matrix res;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res *= a;
        a *= a;
    }
    return res;
}
void solve() {
    ll n;
    cin >> n;
    if (n == 0) {
        cout << 0 << '\n';
    } else {
        cout << pow(matrix(0, 1, 1, 1), n - 1).get() << '\n';
    }
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