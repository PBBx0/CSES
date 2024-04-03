#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
using ll = int64_t;
using ld = long double;

namespace FFT {
    using ld = long double;
    using C = complex<ld>;
    const int N = 1 << 19;
    ll rev[N]{0};
    C root[N];
    C fst[N], snd[N], trd[N];

    void init() {
        for (int i = 0; i < N; ++i) {
            rev[i] = (rev[i >> 1] >> 1) + (i & 1) * (N >> 1);
        }
        for (int i = 0; i < N / 2; ++i) {
            ld alp = 2 * M_PI * i / N;
            root[i + N / 2] = {cos(alp), sin(alp)};
        }
        for (int i = N / 2 - 1; i >= 0; --i) {
            root[i] = root[2 * i];
        }
    }

    void dft(C *f) {
        for (int i = 0; i < N; ++i) if (i > rev[i]) swap(f[i], f[rev[i]]);
        for (int k = 1; k < N; k <<= 1) {
            for (int i = 0; i < N; i += (k << 1)) {
                for (int j = 0; j < k; ++j) {
                    C z = root[j + k] * f[i + j + k];
                    f[i + j + k] = f[i + j] - z;
                    f[i + j] = f[i + j] + z;
                }
            }
        }
    }
}

const int N = 4e5 + 5;
ll a[N], b[N], res[N];

void mult(ll *a, ll *b, ll *res) {
    fill(FFT::fst, FFT::fst + FFT::N, 0);
    fill(FFT::snd, FFT::snd + FFT::N, 0);
    fill(res, res + N, 0);
    for (int i = 0; i < N; ++i) FFT::fst[i].real(a[i]), FFT::snd[i].real(b[i]);
    FFT::dft(FFT::fst), FFT::dft(FFT::snd);
    for (int i = 0; i < FFT::N; ++i) {
        FFT::trd[i] = FFT::fst[i] * FFT::snd[i];
    }
    FFT::dft(FFT::trd);
    reverse(FFT::trd + 1, FFT::trd + FFT::N);
    for (int i = 0; i < FFT::N; ++i) FFT::trd[i] /= (ld) FFT::N;
    for (int i = 0; i < N; ++i) {
        res[i] = (ll) roundl(FFT::trd[i].real());
    }
}

void solve() {
    FFT::init();
    int k, n, m;
    cin >> k >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a[x]++;
    }
    for (int j = 0; j < m; ++j) {
        int x;
        cin >> x;
        b[x]++;
    }
    mult(a, b, res);
    for (int i = 2; i <= k * 2; ++i) cout << res[i] << ' ';
    cout << '\n';
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