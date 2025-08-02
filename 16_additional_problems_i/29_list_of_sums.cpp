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

void solve() {
    int n;
    cin >> n;
    vector<int> b(n * (n - 1) / 2), a;
    a.reserve(n);
    map<int, int> cnt;

    for (int& el : b) cin >> el;
    sort(all(b));
    int sum01 = b[0], sum02 = b[1];
    for (int i = 3; i <= n; ++i) {
        int sum12 = b[i - 1];
        {
            if ((sum01 + sum02 - sum12) <= 0 || (sum01 + sum02 - sum12) % 2 != 0) {
                continue;
            }
            bool ok = true;
            int front = (sum01 + sum02 - sum12) / 2;
            a.clear();
            a.emplace_back(front);
            cnt.clear();
            for (int el : b) ++cnt[el];
            int mx = a[0];
            for (int s = 1; s < n; ++s) {
                auto [x, c] = *cnt.begin();
                int el = x - a[0];
                if (el < mx) {
                    ok = false;
                    break;
                }
                mx = el;
                for (int t : a) {
                    int sm = t + el;
                    auto it = cnt.find(sm);
                    if (it == cnt.end()) {
                        ok = false;
                        break;
                    }
                    --it->second;
                    if (it->second == 0) cnt.erase(it);
                }
                a.emplace_back(el);
            }
            if (ok) {
                for (int el : a) cout << el << ' ';
                cout << '\n';
                return;
            }
        }
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
