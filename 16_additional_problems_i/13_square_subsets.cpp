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

const int ROOT = 70;
const vector<int> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
const vector<int> order = []{
    vector<int> res(ROOT, -1);
    for (int i = 0; i < sz(small_primes); ++i) res[small_primes[i]] = i;
    return res;
}();

vector<int> factorize(int x) {
    vector<int> cur;
    for (int t = 2; t * t <= x; ++t) {
        int cnt = 0;
        while (x % t == 0) {
            x /= t;
            ++cnt;
        }
        if (cnt & 1) cur.emplace_back(t);
    }
    if (x != 1) cur.emplace_back(x);
    return cur;
}

const int MOD = 1e9 + 7;

const int M = 20;
struct xor_basis {
    array<int, M> a;

    bool insert(int x) {
        for (int i = 0; i < M; ++i) {
            if (x >> i & 1) {
                if (a[i] == 0) {
                    a[i] = x;
                    return true;
                } else {
                    x ^= a[i];
                }
            }
        }
        return false;
    }

    int cnt() {
        int res = 0;
        for (int i = 0; i < M; ++i) res += a[i] != 0;
        return res;
    }
};


void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<pair<int, int>> b(n);
    for (int i = 0; i < n; ++i) {
        auto f = factorize(a[i]);
        b[i].first = (f.empty() || f.back() < ROOT) ? 1 : f.back();
        int msz = sz(f) - (b[i].first != 1);
        for (int j = 0; j < msz; ++j) {
            b[i].second |= 1 << (order[f[j]]);
        }
    }
    sort(all(b));
    int last_group = 1, last_mask = 0;
    int dim = 0;
    xor_basis basis{};
    for (auto [gr, mask] : b) {
        if (gr != last_group) {
            ++dim;
            last_mask = mask;
            last_group = gr;
            continue;
        }
        basis.insert(mask ^ last_mask);
    }
    dim += basis.cnt();
    int ans = 1;
    for (int i = 0; i < n - dim; ++i) {
        ans = ans * 2 < MOD ? ans * 2 : ans * 2 - MOD;
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
