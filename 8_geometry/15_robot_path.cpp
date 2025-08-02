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

struct event {
    ll tp, x, y1, y2;
};

bool operator<(const event& a, const event& b) {
    return a.x != b.x ? a.x < b.x
            :   a.tp < b.tp;
}

const ll INF = 1e18;
const int LOG = 20;

void solve() {
    auto start = clock();
    int n;
    cin >> n;
    vector<array<ll, 4>> a(n);
    vector<pair<char, ll>> inp(n);
    ll x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
        char c;
        ll d;
        cin >> c >> d;
        inp[i] = {c, d};
        if (c == 'U') {
            a[i] = {x, y, x, y + d - 1};
            y += d;
        }
        if (c == 'D') {
            a[i] = {x, y, x, y - d + 1};
            y -= d;
        }
        if (c == 'R') {
            a[i] = {x, y, x + d - 1, y};
            x += d;
        }
        if (c == 'L') {
            a[i] = {x, y, x - d + 1, y};
            x -= d;
        }
    }
    for (int i = 1; i < n; ++i) {
        if (inp[i - 1].first == 'L' && inp[i].first == 'R' ||
                inp[i - 1].first == 'R' && inp[i].first == 'L' ||
                inp[i - 1].first == 'U' && inp[i].first == 'D' ||
                inp[i - 1].first == 'D' && inp[i].first == 'U' ) {
            n = i;
            break;
        }
    }
    vector<event> b;
    b.reserve(2 * n);

    auto prepare_events = [&a, &b](int cnt) {
        b.clear();
        for (int i = 0; i < cnt; ++i) {
            auto [x1, y1, x2, y2] = a[i];
            if (x1 == x2) {
                b.emplace_back(0, x1, min(y1, y2), max(y1, y2));
            } else {
                b.emplace_back(-1, min(x1, x2), y1, y1);
                b.emplace_back(1, max(x1, x2), y1, y1);
            }
        }
        sort(all(b));
    };

    auto check = [&b]() {
        set<ll> s;
        set<pair<ll, ll>> seg;
        bool ok = true;
        ll last = -INF;
        for (auto [tp, x, y1, y2] : b) {
            if (x != last) {
                seg.clear();
                last = x;
            }
            if (tp == -1) {
                if (s.contains(y1)) {
                    ok = false;
                    break;
                }
                s.emplace(y1);
            } else if (tp == 0) {
                auto iter = s.lower_bound(y1);
                if (iter != s.end() && *iter <= y2) {
                    ok = false;
                    break;
                }
                auto iter2 = seg.lower_bound({y1, -1});
                if (iter2 != seg.end() && iter2->first <= y2) {
                    ok = false;
                    break;
                }
                if (iter2 != seg.begin() && prev(iter2)->second >= y1) {
                    ok = false;
                    break;
                }
                seg.emplace(y1, y2);
            } else if (tp == 1) {
                s.erase(y1);
            }
        }
        return ok;
    };

    int cnt;
    {
        int l = 0;
        while (true) {
            int mid = 1 << l + 1;
            if (mid > n) break;
            prepare_events(mid);
            if (!check()) break;
            ++l;
        }
        cnt = 0;
        for (int i = l; i >= 0; --i) {
            int mid = cnt + (1 << i);
            if (mid > n) continue;
            prepare_events(mid);
            if (check()) cnt = mid;
        }
    }

    cerr << 1e3 * (clock() - start) / CLOCKS_PER_SEC << '\n';

    ll cur_ans = 0;
    for (int i = 0; i < cnt; ++i) {
        cur_ans += inp[i].second;
    }
    if (cnt == n) {
        cout << cur_ans << '\n';
        return;
    }
    prepare_events(cnt);
    auto& [xfrom, yfrom, xto, yto] = a[cnt];
    auto [dir, delta] = inp[cnt];
    ll sign = (dir == 'U' || dir == 'R') ? 1 : -1;
    ll& var = (dir == 'R' || dir == 'L') ? xto : yto;
    ll from = (dir == 'R' || dir == 'L') ? xfrom : yfrom;

    auto try_this = [&](ll mid) {
        var = from + sign * mid;

        auto [x1, y1, x2, y2] = a[cnt];
        vector<event> cur_events;
        if (x1 == x2) {
            cur_events.emplace_back(0, x1, min(y1, y2), max(y1, y2));
        } else {
            cur_events.emplace_back(-1, min(x1, x2), y1, y1);
            cur_events.emplace_back(1, max(x1, x2), y1, y1);
        }
        for (auto e: cur_events) {
            b.emplace(lower_bound(all(b), e), e);
        }
        bool ok = check();

        for (auto e: cur_events) {
            b.erase(lower_bound(all(b), e));
        }
        return ok;
    };

    ll len;
    {
        int l = -1;
        while (true) {
            ll mid = 1 << l + 1;
            if (mid > delta) break;
            if (!try_this(mid - 1)) break;
            ++l;
        }
        len = 0;
        for (int i = l; i >= 0; --i) {
            ll mid = len + (1 << i);
            if (mid > delta) continue;
            if (try_this(mid - 1)) len = mid;
        }
    }
    cout << cur_ans + len << '\n';

    cerr << 1e3 * (clock() - start) / CLOCKS_PER_SEC << '\n';

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
