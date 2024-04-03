#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
vector<int> pm;
struct seg_tree {
    int N = 1;
    vector<ll> t, sm;
    seg_tree(int n) {
        for (;N < n; N <<= 1);
        t.resize(N << 1);
        sm.resize(N << 1);
    }
    void update(int i, ll x) {
        t[i + N] += x;
        for (int p = i + N; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
        sm[i + N] += x * pm[i];
        for (int p = i + N; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    int get_k(ll k) {
        int v = 1;
        while (v < N) {
            if (t[2 * v] >= k) {
                v *= 2;
            } else {
                k -= t[2 * v];
                v = 2 * v + 1;
            }
        }
        return v - N;
    }
    ll get_sum(int l, int r) {
        ll res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += sm[l++];
            if (r & 1) res += sm[--r];
        }
        return res;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), tmp(k);
    set<int> s;
    for (int& el : a) {cin >> el; s.insert(el); }
    /* coordinates */

    unordered_map<int, int> mp;
    int c = 0;
    for (auto el: s) {
        pm.emplace_back(el);
        mp[el] = c++;
    }
    for (int &el: a) el = mp[el];

    seg_tree st(c);
    for (int i = 0; i < k; ++i) {
        st.update(a[i], 1);
    }
    int kt = (k + 1) >> 1;
    cout << pm[st.get_k(kt)] << ' ';
    for (int i = 1; i + k <= n; ++i) {
        st.update(a[i + k - 1], 1);
        st.update(a[i - 1], -1);
        cout << pm[st.get_k(kt)] << ' ';
    }
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}