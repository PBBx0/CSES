#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    int N = 1;
    vector<int> t, b;
    ST(vector<int>& a) {
        b = a;
        b.emplace_back(-1);
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) t[i + N] = i;
        for (int i = N - 1; i > 0; --i) t[i] = a[t[i + i]] > a[t[i + i + 1]] ? t[i + i] : t[i + i + 1];
    }
    int get(int l, int r) {
        int res = sz(b) - 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res = b[t[l]] > b[res] ? t[l] : res;
                l++;
            }
            if (r & 1) {
                --r;
                res = b[t[r]] > b[res] ? t[r] : res;
            }
        }
        return res;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), gr(n, n);
    for (int& el : a) cin >> el;
    ST seg_tree(a);
    vector<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[i] > a[st.back()]) {
            gr[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    vector<ll> ans(n + 1), p(n + 1);
    for (int i = 0; i < n; ++i) p[i + 1] = p[i] + a[i];
    for (int i = n - 2; i >= 0; --i) {
        int idx = gr[i];
        ans[i] = ans[idx] + 1LL * (idx - i) * a[i] - (p[idx] - p[i]);
    }
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        int x = seg_tree.get(l, r);
        int idx = gr[x];
        ll cur = 1LL * a[x] * (idx - r) - (p[idx] - p[r]);
        cout << ans[l] - cur - ans[idx] << '\n';
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