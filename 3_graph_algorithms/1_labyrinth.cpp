#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const pair<int, int> delta[] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
const char name[] = {'U', 'D', 'R', 'L'};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> field(n);
    field.resize(n);
    for (auto &el: field) cin >> el;
    int is, js, it, jt;
    for (int i = 0; i < n; ++i) {
        auto iter = field[i].find('A');
        if (iter != string::npos) is = i, js = iter;

        iter = field[i].find('B');
        if (iter != string::npos) it = i, jt = iter;
    }
    vector par(n, vector<int>(m, -1));
    par[is][js] = -2;
    deque<pair<int, int>> q;
    q.emplace_back(is, js);
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop_front();
        for (int num = 0; num < 4; ++num) {
            auto [di, dj] = delta[num];
            int i1 = i + di, j1 = j + dj;
            if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) continue;
            if (field[i1][j1] == '#' || par[i1][j1] != -1) continue;
            par[i1][j1] = num;
            q.emplace_back(i1, j1);
        }
    }
    if (par[it][jt] == -1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    string output;
    while (par[it][jt] != -2) {
        output += name[par[it][jt]];
        auto [di, dj] = delta[par[it][jt]];
        it -= di, jt -= dj;
    }
    reverse(all(output));
    cout << sz(output) << '\n' << output << '\n';
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