#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int C = 26, N = 5005;
const ll MOD = 1e9 + 7;
int cnt[C];
ll fact[N], ifact[N];

ll inv(ll x) {
    ll res = 1;
    for (ll pw = MOD - 2; pw > 0; pw >>= 1) {
        if (pw & 1) res = res * x % MOD;
        x = x * x % MOD;
    }
    return res;
}

inline ll CC(ll n, ll k) {
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void mul(vector<ll>& fst, vector<ll>& snd, vector<ll>& rs) {
    rs.resize(fst.size() + snd.size() - 1);
    fill(rs.begin(), rs.end(), 0);
    for (int i = 0; i < sz(fst); ++i) {
        for (int j = 0; j < sz(snd); ++j) {
            (rs[i + j] += fst[i] * snd[j]) %= MOD;
        }
    }
}

void solve() {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % MOD;
    ifact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 1; i > 0; --i) ifact[i - 1] = ifact[i] * i % MOD;

    string str;
    cin >> str;
    for (char el : str) cnt[el - 'a']++;
    vector<ll> f, g{1}, h;
    for (int x : cnt) {
        if (x == 0) continue;
        f.resize(x);
        for (int j = 0; j < x; ++j) {
            f[j] = CC(x - 1, j) * ifact[x - j] % MOD;
            if (j & 1) f[j] = -f[j];
        }
        mul(f, g, h);
        swap(g, h);
        h.clear();
        f.clear();
    }
    ll rs = 0, L = sz(str);
    for (int i = 0; i < sz(g); ++i) {
        (rs += fact[L - i] * g[i]) %= MOD;
    }
    cout << (rs + MOD) % MOD << '\n';
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