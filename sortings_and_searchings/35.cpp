#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e18;
vector<pair<ll, ll>> st1, st2;
void push(ll x) {
    st2.emplace_back(x, min(x, st2.empty() ? INF : st2.back().second));
}
void pop() {
    if (st1.empty()) {
        while (!st2.empty()) {
            st1.emplace_back(st2.back().first, min(st2.back().first, st1.empty() ? INF : st1.back().second));
            st2.pop_back();
        }
    }
    st1.pop_back();
}
ll get() {
    return min(st1.empty() ? INF : st1.back().second,
            st2.empty() ? INF : st2.back().second);
}

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<ll> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + a[i];
    }
    int l1 = 0, r1 = 0;
    ll res = -INF;
    bool empty = true;

    for (int i = 1; i <= n; ++i) {
        while (r1 <= i - l) {
            push(p[r1++]);
            empty = false;
        }
        while (l1 < i - r) {
            pop();
            ++l1;
        }
        if (!empty)
            res = max(res, p[i] - get());
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}