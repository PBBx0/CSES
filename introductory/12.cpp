#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
const int C = 26;
void solve() {
    string s;
    cin >> s;
    vector<int> cnt(C, 0);
    for (auto el : s) cnt[el - 'A']++;
    int tmp = 0;
    for (int el : cnt) tmp += el & 1;
    if (tmp > 1) {
        cout << "NO SOLUTION\n";
        return;
    }
    int pos = -1;
    string out;
    for (int i = 0; i < C; ++i) {
        if (cnt[i] & 1) {
            pos = i;
        } else {
            for (int _ = 0; _ < cnt[i] / 2; ++_)
                out.push_back(char('A' + i));
        }
    }
    if (pos != -1) {
        for (int _ = 0; _ < cnt[pos] / 2; ++_) {
            out.push_back(char('A' + pos));
        }
        cout << out;
        out.push_back(char('A' + pos));
        reverse(out.begin(), out.end());
        cout << out << '\n';
        return;
    }
    cout << out;
    reverse(out.begin(), out.end());
    cout << out << '\n';
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