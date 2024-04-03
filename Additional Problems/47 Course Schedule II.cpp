#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
vector<int> g[N];
int deg[N];
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        a--, b--;
        g[b].emplace_back(a);
        deg[a]++;
    }
    set<int> s;
    for (int v = 0; v < n; v++) if (deg[v] == 0) s.insert(v);
    int ans[n];
    for (int i = n - 1; i >= 0; --i) {
        int v = *s.rbegin();
        s.erase(--s.end());
        ans[i] = v + 1;
        for (int to : g[v]) {
            --deg[to];
            if (!deg[to]) s.insert(to);
        }
    }
    for (int v : ans) cout << v << ' ';
    cout << '\n';
}