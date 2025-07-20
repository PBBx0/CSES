#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ll = int64_t;

string ask(string s) {
    cout << "? " << s << endl;
    cin >> s;
    return s;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    string s(n, '0');
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < n; ++j) {
            s[j] = '0' + (j >> i & 1);
        }
        s = ask(s);
        for (int j = 0; j < n; ++j) {
            a[j] |= (s[j] - '0') << i;
        }
    }
    cout << "! ";
    for (int el : a) cout << el + 1 << ' ';
    cout << '\n';
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
