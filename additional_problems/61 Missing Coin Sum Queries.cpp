#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    int N = 1;
    struct node {
        ll sum = 1;
        vector<ll> v, pref;
        node() : pref(1) {}
    };
    vector<node> t;
    ST(const vector<ll> & a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) {
            if (a[i] == 1) {
                t[i + N].sum++;
            } else {
                t[i + N].v.emplace_back(a[i]);
                t[i + N].pref.emplace_back(a[i]);
            }
        }
        for (int i = N - 1; i > 0; --i) {
            t[i].sum = t[i + i].sum + t[i + i + 1].sum - 1;
            int r1 = 0, r2 = 0;
            ll & x = t[i].sum;
            for (bool ok = true; ok;) {
                ok = false;
                int cnt1 = std::upper_bound(t[i + i].v.begin(), t[i + i].v.end(), x) - t[i + i].v.begin();
                if (cnt1 > r1) ok = true;
                x += t[i + i].pref[cnt1] - t[i + i].pref[r1];
                r1 = cnt1;
                int cnt2 = std::upper_bound(t[i + i + 1].v.begin(), t[i + i + 1].v.end(), x) - t[i + i + 1].v.begin();
                if (cnt2 > r2) ok = true;
                x += t[i + i + 1].pref[cnt2] - t[i + i + 1].pref[r2];
                r2 = cnt2;
            }
            t[i].v.resize(t[i + i].v.size() - r1 + t[i + i + 1].v.size() - r2);
            std::merge(t[i + i].v.begin() + r1, t[i + i].v.end(),
                       t[i + i + 1].v.begin() + r2, t[i + i + 1].v.end(),
                       t[i].v.begin());
            t[i].pref.resize(t[i].v.size() + 1);
            for (int j = 0; j < sz(t[i].v); ++j) {
                t[i].pref[j + 1] = t[i].pref[j] + t[i].v[j];
            }
        }
    }
    inline ll get(int l, int r) {
        vector<int> vts;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) vts.emplace_back(l++);
            if (r & 1) vts.emplace_back(--r);
        }
        ll sum = 1;
        for (int v : vts) sum += t[v].sum - 1;
        int n = sz(vts);
        vector<int> bd(n);
        for (bool ok = true; ok;) {
            ok = false;
            for (int i = 0; i < n; ++i) {
                int v = vts[i];
                if (bd[i] == sz(t[v].v) || t[v].v[bd[i]] > sum) continue;
                ok = true;
                int nbd = std::upper_bound(t[v].v.begin() + bd[i], t[v].v.end(), sum) - t[v].v.begin();
                sum += t[v].pref[nbd] - t[v].pref[bd[i]];
                bd[i] = nbd;
            }
        }
        return sum;
    }
};
void solve() {
    auto start = ::clock();
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll & el : a) cin >> el;
    ST st(a);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << st.get(--l, r) << '\n';
    }
    cerr << (::clock() - start) * 1e3 / CLOCKS_PER_SEC << '\n';
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