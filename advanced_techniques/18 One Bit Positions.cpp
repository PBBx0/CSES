#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
using ld = long double;
const ll N = 1 << 19, LOGN = 18;
ll rev(ll x) {
    ll res = 0;
    for (ll i = 0; i <= LOGN; ++i) {
        if (x & (1 << i)) {
            res += (1 << (LOGN - i));
        }
    }
    return res;
}

void call(vector<complex<ld>> &d, ll l, ll r) {
    ll n = r - l;
    if (n == 1) {
        return;
    }
    call(d, l, (l + r) / 2);
    call(d, (l + r) / 2, r);
    complex<ld> w(cos(2 * M_PI / n), sin(2 * M_PI / n)), tmp(1, 0);
    for (ll i = l; i < (l + r) / 2; ++i) {
        auto da = d[i], db = d[i + n / 2];
        d[i] = da + db * tmp;
        d[i + n / 2] = da - db * tmp;
        tmp *= w;
    }
}

vector<complex<ld>> dft(vector<complex<ld>> f) {
    for (ll i = 0; i < N; ++i) {
        if (i > rev(i)) {
            swap(f[i], f[rev(i)]);
        }
    }
    call(f, 0, N);
    return f;
}
void solve() {
    string s;
    cin >> s;
    int n = sz(s);
    vector<complex<ld>> f(N), g(N);
    for (int i = 0; i < n; ++i) if (s[i] == '1') {
        f[i].real(1);
        g[n - i].real(1);
    }
    f = dft(f), g = dft(g);
    for (int i = 0; i < N; ++i) f[i] *= g[i];
    f = dft(f);
    vector<ll> res(N);
    res[0] = (ll) ::round(f[0].real() / N);
    for (int i = 1; i < N; ++i) {
        res[i] = (ll) ::round(f[N - i].real() / N);
    }
    for (int k = 1; k < n; ++k) {
        cout << res[k + n] << ' ';
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