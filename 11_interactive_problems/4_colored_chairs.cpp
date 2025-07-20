#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ll = int64_t;

bool ask(int i) {
    cout << "? " << i + 1 << endl;
    char x;
    cin >> x;
    return x == 'R';
}

void answer(int i) {
    cout << "! " << i + 1 << endl;
    exit(EXIT_SUCCESS);
}

void solve() {
    int n;
    cin >> n;
    int l = 0, r = n - 1;
    bool fl = ask(l);
    bool fr = ask(r);
    if (fl == fr) {
        answer(r);
    }
    while (r - l + 1 > 2) {
        int mid = (l + r) / 2;
        bool f = ask(mid);
        int len1 = mid - l + 1;
        int len2 = r - mid + 1;
        if ((f == fl && len1 % 2 == 0) || (f != fl && len1 % 2 == 1)) {
            r = mid;
            fr = f;
        } else {
            l = mid;
            fl = f;
        }
    }
    answer(l);
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
