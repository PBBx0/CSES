#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), ans(n, -1), st;
    for (int& el : a) cin >> el;
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && a[i] < a[st.back()]) {
            ans[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    for (auto el : ans) cout << el + 1 << ' ';
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