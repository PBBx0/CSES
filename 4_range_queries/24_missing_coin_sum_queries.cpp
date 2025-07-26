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

struct ST {
    int N = 1;
    vector<ll> t;
    vector<vector<ll>> ar, pref;

    explicit ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        ar.resize(N << 1);
        pref.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            if (a[i] == 1) {
                t[i + N] = 1;
            } else {
                ar[i + N].emplace_back(a[i]);
                pref[i + N].emplace_back(0);
                pref[i + N].emplace_back(a[i]);
            }
        }
        for (int i = N - 1; i > 0; --i) {
            int l = i << 1 | 0, r = i << 1 | 1;
            t[i] = t[l] + t[r];
            int pl = 0, pr = 0;
            while (pl < sz(ar[l]) && pr < sz(ar[r]) && t[i] + 1 >= min(ar[l][pl], ar[r][pr])) {
                if (ar[l][pl] <= ar[r][pr]) {
                    t[i] += ar[l][pl];
                    ++pl;
                } else {
                    t[i] += ar[r][pr];
                    ++pr;
                }
            }
            while (pl < sz(ar[l]) && t[i] + 1 >= ar[l][pl]) {
                t[i] += ar[l][pl];
                ++pl;
            }
            while (pr < sz(ar[r]) && t[i] + 1 >= ar[r][pr]) {
                t[i] += ar[r][pr];
                ++pr;
            }
            int s = sz(ar[l]) - pl + sz(ar[r]) - pr;
            ar[i].resize(s);
            merge(ar[l].begin() + pl, ar[l].end(), ar[r].begin() + pr, ar[r].end(), ar[i].begin());
            pref[i].resize(s + 1);
            for (int j = 0; j < s; ++j) pref[i][j + 1] = pref[i][j] + ar[i][j];
        }
    }

    ll get(int l, int r) {
        vector<int> vtx;
        ll ans = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                ans += t[l];
                vtx.emplace_back(l);
                ++l;
            }
            if (r & 1) {
                --r;
                ans += t[r];
                vtx.emplace_back(r);
            }
        }
        int n = sz(vtx);
        vector<int> ptr(n);
        for (bool updated = true; updated; ) {
            updated = false;
            for (int i = 0; i < n; ++i) {
                int v = vtx[i];
                if (ptr[i] == sz(ar[v]) || ar[v][ptr[i]] > ans) continue;
                int nptr = upper_bound(ar[v].begin() + ptr[i], ar[v].end(), ans) - ar[v].begin();
                if (nptr > ptr[i]) {
                    updated = true;
                    ans += pref[v][nptr] - pref[v][ptr[i]];
                    ptr[i] = nptr;
                }
            }
        }
        return ans;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ST st(a);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << st.get(l, r) << '\n';
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
