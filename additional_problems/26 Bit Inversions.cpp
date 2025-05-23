#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    string str;
    cin >> str;
    int n = sz(str);
    set<int> szs;
    int cnt_sz[n + 1];
    fill(cnt_sz, cnt_sz + n + 1, 0);
    set<int> s{0, n};
    int last = 0;
    for (int i = 1; i < n; ++i) {
        if (str[i] != str[i - 1]) {
            s.insert(i);
            szs.insert(i - last);
            cnt_sz[i - last]++;
            last = i;
        }
    }
    szs.insert(n - last);
    cnt_sz[n - last]++;
    auto remove = [&](int x) {
        cnt_sz[x]--;
        if (!cnt_sz[x]) szs.erase(x);
    };
    auto add = [&](int x) {
        if (!cnt_sz[x]) szs.insert(x);
        cnt_sz[x]++;
    };
    auto get = [&]() {
        return *szs.rbegin();
    };
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int p;
        cin >> p;
        p--;
        auto it = s.upper_bound(p);
        int l = *prev(it), r = *it;
        remove(r - l);
        if (p == l && p + 1 == r) {
            int l2 = 0, r2 = n;
            if (l != 0) {
                l2 = *prev(s.lower_bound(l));
                s.erase(l);
                remove(l - l2);
            }
            if (r != n) {
                r2 = *s.upper_bound(r);
                s.erase(r);
                remove(r2 - r);
            }
            add(r2 - l2);
        } else if (p == l) {
            int l2 = 0;
            if (l != 0) {
                l2 = *prev(s.lower_bound(l));
                s.erase(l);
                remove(l - l2);
            }
            s.insert(p + 1);
            add(p + 1 - l2);
            add(r - p - 1);
        } else if (p + 1 == r) {
            int r2 = n;
            if (r != n) {
                r2 = *s.upper_bound(r);
                s.erase(r);
                remove(r2 - r);
            }
            s.insert(p);
            add(p - l);
            add(r2 - p);
        } else {
            add(p - l);
            add(1);
            add(r - p - 1);
            s.insert(p), s.insert(p + 1);
        }
        cout << get() << ' ';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}