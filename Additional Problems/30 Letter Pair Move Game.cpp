#include <bits/stdc++.h>
#define sz(n) (int)(n).size()

using namespace std;
int vid, n, cnt = 0;
string s, s2;
bool print = false;
void turn(int i) {
    ++cnt;
    swap(s[vid], s[i]), swap(s[vid + 1], s[i + 1]);
    vid = i;
    if (print) cout << s << '\n';
}
void my_swap(int i, int j) {
    int tmp = vid;
    turn(i);
    turn(j);
    turn(tmp);
}
bool match(int i, string pattern) {
    if (2 * n - i != sz(pattern)) return false;
    for (int j = 0; j < sz(pattern); ++j) {
        if (s[i + j] != pattern[j]) return false;
    }
    return true;
}
bool solve() {
    vid = 0;
    while (s[vid] != '.') vid++;
    if (n <= 2) {
        char fst = '.';
        for (int i = 0; i < 2 * n; ++i) {
            if (s[i] != '.') {
                fst = s[i];
                break;
            }
        }
        if (fst == 'B') {
            return false;
        } else {
            return true;
        }
    }
    //move empty boxes to an end
    if (vid != 2 * n - 2) {
        if (vid == 2 * n - 3) {
            turn(0);
        }
        turn(2 * n - 2);
    }
    //connect two 'B's
    int bid = -1;
    for (int i = 0; i < 2 * n - 1; ++i) {
        if (s[i] == 'B' && s[i + 1] == 'B') {
            bid = i;
            break;
        }
    }
    if (bid == -1) {
        int b0id = -1, b1id = -1;
        for (int i = 0; i < 2 * n; ++i) {
            if (s[i] == 'B' && b0id == -1) {
                b0id = i;
            } else if (s[i] == 'B') {
                b1id = i;
                break;
            }
        }
        if (s[b1id + 1] == '.') {
//            my_swap(b0id, b1id + 1);
            turn(b0id);
        } else if (b1id - b0id != 2) {
            my_swap(b1id, b0id + 1);
        } else {
            int tmp = vid;
            turn(b0id);
            turn(tmp - 1);
        }
    } else if (bid > 1) {
        if (bid == 1) {
            my_swap(bid, 3);
        }
        my_swap(bid, 0);
    }
    bid = -1;
    for (int i = 0; i < 2 * n - 1; ++i) {
        if (s[i] == 'B' && s[i + 1] == 'B') {
            bid = i;
            break;
        }
    }
    assert(bid != -1);
    //
    if (vid < bid) { turn(bid); }
    if (vid < 2 * n - 3) { turn(2 * n - 2); }
    for (bid = 0; s[bid] == 'A'; ++bid);
    int last = bid;
    while (s[last] == 'B') ++last;
    while (true) {
        for (bid = 0; s[bid] == 'A'; ++bid);
        if (s[last] == 'B') {
            ++last;
        } else if (s[last] == 'A') {
            if (s[last + 1] != '.') {
                my_swap(last, bid);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if (match(last, "..A")) {
        if (n == 3) {
            return false;
        }
        turn(0);
        turn(2 * n - 2);
        for (bid = 0; s[bid] == 'A'; ++bid);
        turn(bid - 1);
        turn(2 * n - 3);
    } else if (match(last, "A..B")) {
        turn(bid - 1);
        turn(2 * n - 4);
    } else if (match(last, "A..A")) {
        turn(bid);
        turn(2 * n - 4);
        turn(2 * n - 2);
        for (bid = 0; s[bid] == 'A'; ++bid);
        turn(bid - 1);
        turn(2 * n - 3);
    } else if (match(last, "A..")) {
        turn(bid - 1);
        turn(2 * n - 3);
    }
    return true;
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    cin >> n >> s;
    s2 = s;
    if (solve()) {
        s = s2;
        cout << cnt << '\n';
        print = true;
        solve();
    } else {
        cout << -1 << '\n';
    }
    return 0;
}
