#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

pair<int, int> shift[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
char direction[] = {'U', 'L', 'D', 'R'};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> field(n);
    for (auto& el : field) cin >> el;
    deque<pair<int, int>> q;
    vector dist_me(n, vector<int>(m, -1));
    vector par_me(n, vector<int>(m, -1));
    vector dist_monster(n, vector<int>(m, -1));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (field[i][j] == 'M') {
            dist_monster[i][j] = 0;
            q.emplace_back(i, j);
        }
    }
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop_front();
        for (auto [di, dj] : shift) {
            int i1 = i + di, j1 = j + dj;
            if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) continue;
            if (field[i1][j1] == '#' || dist_monster[i1][j1] != -1) continue;
            dist_monster[i1][j1] = dist_monster[i][j] + 1;
            q.emplace_back(i1, j1);
        }
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (field[i][j] == 'A') {
            dist_me[i][j] = 0;
            q.emplace_back(i, j);
        }
    }
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop_front();
        for (int id = 0; id < 4; ++id) {
            auto [di, dj] = shift[id];
            int i1 = i + di, j1 = j + dj;
            if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) continue;
            if (field[i1][j1] == '#' || dist_me[i1][j1] != -1) continue;
            if (dist_monster[i1][j1] != -1 && dist_me[i][j] + 1 >= dist_monster[i1][j1]) continue;
            dist_me[i1][j1] = dist_me[i][j] + 1;
            par_me[i1][j1] = id;
            q.emplace_back(i1, j1);
        }
    }
    int a_i = -1, a_j = -1;
    for (int i = 0; i < n; ++i) for (int j : {0, m - 1}) {
        if (dist_me[i][j] != -1) {
            a_i = i, a_j = j;
        }
    }
    for (int i : {0, n - 1}) for (int j = 0; j < m; ++j) {
        if (dist_me[i][j] != -1) {
            a_i = i, a_j = j;
        }
    }
    if (a_i == -1 && a_j == -1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    string outp;
    while (par_me[a_i][a_j] != -1) {
        int d = par_me[a_i][a_j];
        outp += direction[d];
        a_i -= shift[d].first;
        a_j -= shift[d].second;
    }
    reverse(all(outp));
    cout << sz(outp) << '\n' << outp << '\n';
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