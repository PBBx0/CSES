#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int & el : a) cin >> el;
    vector ltl(n, -1), ltr(n, n);
    vector<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] > a[i]) {
            ltr[st.back()] = i;
            st.pop_back();
        }
        if (!st.empty())
            ltl[i] = a[i] == a[st.back()] ? ltl[st.back()] : st.back();
        st.push_back(i);
    }
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        res = max(res, (ll)a[i] * (ltr[i] - ltl[i] - 1));
    }
    cout << res << '\n';
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