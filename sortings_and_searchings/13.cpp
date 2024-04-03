#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
const int N = 2e5;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> s;
    for (int& el : a) {
        cin >> el;
        s.insert(el);
    }
    unordered_map<int, int> mp;
    mp.reserve(n);
    int c = 0;
    for (int i : s) mp[i] = c++;
    for (int & el : a) el = mp[el];
    bool used[N];
    fill(used, used + c, false);
    int i = 0, res = 1;
    for (int j = 0; j < n; ++j) {
        while (used[a[j]]) {
            used[a[i++]] = false;
        }
        used[a[j]] = true;
        res = max(res, j - i + 1);
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
    solve();
    return 0;
}