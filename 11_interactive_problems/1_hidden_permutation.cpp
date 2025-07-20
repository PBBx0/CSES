#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ll = int64_t;

bool ask(int i, int j) {
    cout << "? " << i + 1 << ' ' << j + 1 << endl;
    string res;
    cin >> res;
    return res == "YES";
}

void solve() {
    int n;
    cin >> n;
    vector<int> order;
    for (int i = 0; i < n; ++i) {
        int lo = -1, hi = sz(order);
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            (ask(order[mid], i) ? lo : hi) = mid;
        }
        order.emplace(order.begin() + hi, i);
    }
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[order[i]] = i;
    cout << "! ";
    for (int el : perm) cout << el + 1 << ' ';
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
