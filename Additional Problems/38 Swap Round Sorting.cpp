#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int & x : a) {cin >> x; --x;}
    int ans = 0;
    bool used[n];
    fill(used, used + n, false);
    int p[n];
    int top = 0;
    auto add = [&](int v) {
        for (; !used[v]; v = a[v]) {
            p[top++] = v;
            used[v] = true;
        }
    };
    vector<pair<int, int>> out;
    function<void(int, int)> process = [&](int l, int r) {
        if (r - l <= 2) return;
        if (r - l <= 4) {
            out.emplace_back(p[l + 1], p[r - 1]);
            swap(a[p[l + 1]], a[p[r - 1]]);
            return;
        }
        out.emplace_back(p[l + 1], p[r - 1]);
        out.emplace_back(p[l + 2], p[r - 2]);
        swap(a[p[l + 1]], a[p[r - 1]]);
        swap(a[p[l + 2]], a[p[r - 2]]);
        process(l + 2, r - 2);
    };
    for (int x = 0; x < n; ++x) if (!used[x]) {
        int l = top;
        add(x);
        int r = top;
        if (r - l > 1) ans = max(ans, 1);
        if (r - l > 2) {
            ans = max(ans, 2);
            process(l, r);
        }
    }
    cout << ans << '\n';
    if (ans == 2) {
        cout << sz(out) << '\n';
        for (auto [x, y] : out) cout << x + 1 << ' ' << y + 1 << '\n';
    }
    if (ans == 0) return;
    out.clear();
    fill(used, used + n, false);
    top = 0;
    for (int x = 0; x < n; ++x) {
        int l = top;
        add(x);
        int r = top;
        assert(r - l <= 2);
        if (r - l == 2) {
            out.emplace_back(p[l], p[l + 1]);
            swap(a[p[l]], a[p[l + 1]]);
        }
    }
    cout << sz(out) << '\n';
    for (auto [x, y] : out) cout << x + 1 << ' ' << y + 1 << '\n';
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