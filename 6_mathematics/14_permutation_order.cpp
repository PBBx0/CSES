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

ll fact[21];

vector<int> permutation_by_number(int n, ll k) {
    vector<int> p(n), ans(n);
    iota(all(p), 0);
    for (int i = 0; i < n; ++i) {
        int l = n - i - 1;
        for (int j = 0; j < n - i; ++j) {
            if (k < fact[l]) {
                ans[i] = p[j];
                p.erase(p.begin() + j);
                break;
            } else {
                k -= fact[l];
            }
        }
    }
    return ans;
}

ll number_by_permutation(int n, const vector<int>& p) {
    vector<int> a(n);
    iota(all(a), 0);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int l = n - i - 1;
        auto iter = lower_bound(all(a), p[i]);
        int pos = iter - a.begin();
        ans += pos * fact[l];
        a.erase(iter);
    }
    return ans;
}

void solve() {
    fact[0] = 1;
    for (int i = 1; i < 21; ++i) fact[i] = 1LL * fact[i - 1] * i;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int tp, n;
        cin >> tp >> n;
        if (tp == 1) {
            ll k;
            cin >> k;
            auto cur = permutation_by_number(n, k - 1);
            for (int el : cur) cout << el + 1 << ' ';
            cout << '\n';
        } else {
            vector<int> a(n);
            for (int& el : a) {
                cin >> el;
                --el;
            }
            cout << number_by_permutation(n, a) + 1 << '\n';
        }
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
    solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
