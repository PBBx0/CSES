#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    int m = n * (n - 1) / 2;
    int b[m];
    multiset<int> sms;
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    vector<int> a;
    auto check = [&]() {
        for (int el : b) sms.insert(el);
        sms.erase(sms.find(a[0] + a[1]));
        sms.erase(sms.find(a[0] + a[2]));
        sms.erase(sms.find(a[1] + a[2]));
        int a0 = a[0];
        while (!sms.empty()) {
            int x = *sms.begin() - a0;
            if (x < a.back()) return false;
            sms.erase(sms.begin());
            for (int i = 1; i < sz(a); ++i) {
                if (!sms.contains(x + a[i])) return false;
                sms.erase(sms.find(x + a[i]));
            }
            a.emplace_back(x);
        }
        for (int el : a) cout << el << ' ';
        return true;
    };
    sort(b, b + m);
    int r1 = b[0], r2 = b[1];
    for (int j = 2; j < m; ++j) {
        int r = b[j];
        if ((r1 + r2 + r) & 1) continue;
        a.emplace_back((r1 + r2 - r) >> 1);
        a.emplace_back((r1 + r - r2) >> 1);
        a.emplace_back((r2 + r - r1) >> 1);
        sms.clear();
        if (check()) return;
        a.clear();
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