#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int C = 26;
int cnt[C];
bool check() {
    int mx = 0, sm = 0;
    for (int c : cnt) {
        mx = max(mx, c);
        sm += c;
    }
    return mx * 2 - 1 <= sm;
}
void solve() {
    string s;
    cin >> s;
    for (char x : s) cnt[x - 'A']++;
    int n = sz(s);
    if (!check()) {
        cout << -1 << '\n';
        return;
    }
    string out;
    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < C; ++x) if (cnt[x] && (out.empty() || x != out.back() - 'A')) {
            cnt[x]--;
            if (check()) {
                out += char(x + 'A');
                break;
            }
            cnt[x]++;
        }
    }
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}