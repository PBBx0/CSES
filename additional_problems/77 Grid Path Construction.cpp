#include <bits/stdc++.h>
#define sz(n) (int)(n).size()

using namespace std;

void expect(bool expression, const string& message) {
    if (!expression) {
        cerr << message << '\n';
        assert(false);
    }
}

bool exists_path(int n, int m, int i1, int j1, int i2, int j2) {
    if (n == 0 || m == 0) return true;
    if (!(i1 >= 1 && i1 <= n && i2 >= 1 && i2 <= n && j1 >= 1 && j1 <= m && j2 >= 1 && j2 <= m)) return false;
    if (i1 == i2 && j1 == j2) return false;
    if (n > m) swap(n, m), swap(i1, j1), swap(i2, j2);
    if (j1 > j2) swap(i1, i2), swap(j1, j2);


    if (n * m % 2 == 1 && ((i1 + j1) & 1 | (i2 + j2) & 1) == 1) return false;
    if (n * m % 2 == 0 && (i1 + j1 + i2 + j2) % 2 == 0) return false;

    if (n == 1) return j1 == 1 && j2 == m;
    if (n == 2) {
        if (j1 == j2) return j1 == 1 || j1 == m;
        return j2 > j1 + 1 || i1 == i2;
        //return j1 == j2 ? (j1 == 1 || j1 == m) : (abs(j1 - j2) > 1);
    }
    if (n == 3) {
        if ((i1 + j1) % 2 == 0) return true;
        return !((i1 == 2 && j1 != j2) || (i1 != 2 && j2 > j1 + 1));
    }
    return true;
}

bool exists_cycle(int n, int m) {
    return n * m % 2 == 0 && min(n, m) > 1;
}

const int N = 52;
/* 0 -> U; 1 -> R; 2 -> D; 3 -> L */
int nxt[2][N][N];
int used[N][N];
bool painted[N][N];
constexpr pair<int, int> shift[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

char dir_to_char(int d) {
    if (d == 0) return 'U';
    if (d == 1) return 'R';
    if (d == 2) return 'D';
    if (d == 3) return 'L';
    //todo remove
    if (d == -1) return '.';
    expect(false, "incorrect nxt value");
}

void print_path(int i1, int j1, int i2, int j2) {
    for (int i = i1; i <= i2; ++i) {
        for (int j = j1; j <= j2; ++j) {
            cerr << dir_to_char(nxt[1][i][j]);
        }
        cerr << '\n';
    }
    cerr << '\n';
}

void invert_direction(int i1, int j1, int i2, int j2) {
    for (int i = i1; i <= i2; ++i) {
        for (int j = j1; j <= j2; ++j) {
            swap(nxt[0][i][j], nxt[1][i][j]);
        }
    }
}

void paint(int i1, int j1, int i2, int j2) {
    for (int i = i1; i  <= i2; ++i) {
        for (int j = j1; j <= j2; ++j) {
            painted[i][j] = true;
        }
    }
}

bool move(int& i, int& j, int d, int reverse = 0) {
    auto [di, dj] = shift[d];
    if (painted[i + di][j + dj]) return false;
    nxt[1 - reverse][i][j] = d;
    i += di, j += dj;
    nxt[reverse][i][j] = d ^ 2;
    return painted[i][j] = true;
}

//todo build top cycle;
void build_trivial_cycle(int i1, int j1, int i2, int j2, bool left) {
    int n = i2 - i1 + 1, m = j2 - j1 + 1;
    if (min(n, m) <= 0) return;
    expect(n * m % 2 == 0 && min(n, m) > 1, "cycle does not exists");

    paint(i1, j1, i2, j2);
    nxt[0][i1][j1] = 2, nxt[1][i1][j1] = 1;
    nxt[0][i1][j2] = 3, nxt[1][i1][j2] = 2;
    nxt[0][i2][j1] = 1, nxt[1][i2][j1] = 0;
    nxt[0][i2][j2] = 0, nxt[1][i2][j2] = 3;
    if (m % 2 == 0) {
        for (int j = j1 + 1; j < j2; ++j) {
            nxt[0][i1][j] = 3, nxt[1][i1][j] = 1;
        }
        if (n == 2) {
            for (int j = j1 + 1; j < j2; ++j) {
                nxt[0][i2][j] = 1, nxt[1][i2][j] = 3;
            }
        } else {
            for (int j = j1; j <= j2; j += 2) {
                for (int i = i1 + 1; i < i2; ++i) {
                    nxt[0][i][j] = 2, nxt[1][i][j] = 0;
                    nxt[0][i][j + 1] = 0, nxt[1][i][j + 1] = 2;
                }
                nxt[0][i2][j] = 1, nxt[1][i2][j] = 0;
                nxt[0][i2][j + 1] = 0, nxt[1][i2][j + 1] = 3;
            }
            for (int j = j1 + 1; j < j2; j += 2) {
                nxt[0][i1 + 1][j] = 1, nxt[1][i1 + 1][j] = 2;
                nxt[0][i1 + 1][j + 1] = 2, nxt[1][i1 + 1][j + 1] = 3;
            }
        }
    } else if (left) {
        for (int i = i1 + 1; i < i2; ++i) {
            nxt[0][i][j2] = 0, nxt[1][i][j2] = 2;
        }
        for (int i = i1; i <= i2; i += 2) {
            for (int j = j1 + 1; j < j2; ++j) {
                nxt[0][i][j] = 3, nxt[1][i][j] = 1;
                nxt[0][i + 1][j] = 1, nxt[1][i + 1][j] = 3;
            }
            nxt[0][i][j1] = 2, nxt[1][i][j1] = 1;
            nxt[0][i + 1][j1] = 1, nxt[1][i + 1][j1] = 0;
        }
        for (int i = i1 + 1; i < i2; i += 2) {
            nxt[0][i][j2 - 1] = 2, nxt[1][i][j2 - 1] = 3;
            nxt[0][i + 1][j2 - 1] = 3, nxt[1][i + 1][j2 - 1] = 0;
        }
    } else {
        for (int i = i1 + 1; i < i2; ++i) {
            nxt[0][i][j1] = 2, nxt[1][i][j1] = 0;
        }
        for (int i = i1; i <= i2; i += 2) {
            for (int j = j1 + 1; j < j2; ++j) {
                nxt[0][i][j] = 3, nxt[1][i][j] = 1;
                nxt[0][i + 1][j] = 1, nxt[1][i + 1][j] = 3;
            }
            nxt[0][i][j2] = 3, nxt[1][i][j2] = 2;
            nxt[0][i + 1][j2] = 0, nxt[1][i + 1][j2] = 3;
        }
        for (int i = i1 + 1; i < i2; i += 2) {
            nxt[0][i][j1 + 1] = 1, nxt[1][i][j1 + 1] = 2;
            nxt[0][i + 1][j1 + 1] = 0, nxt[1][i + 1][j1 + 1] = 1;
        }
    }
}



bool add_left(int i, int j, int u, int l, int d, int r) {
    if (nxt[1][i][j] == 2) {
        if (nxt[1][i][j - 1] == 2) invert_direction(u, l, d, r);
        if (nxt[0][i][j - 1] == 2) {
            nxt[1][i][j] = 3, nxt[0][i][j - 1] = 1;
            nxt[1][i + 1][j - 1] = 1, nxt[0][i + 1][j] = 3;
            return true;
        }
    } else if (nxt[1][i][j] == 0) {
        if (nxt[1][i][j - 1] == 0) invert_direction(u, l, d, r);
        if (nxt[0][i][j - 1] == 0) {
            nxt[1][i][j] = 3, nxt[0][i][j - 1] = 1;
            nxt[1][i - 1][j - 1] = 1, nxt[0][i - 1][j] = 3;
            return true;
        }
    }
    return false;
}

bool add_right(int i, int j, int u, int l, int d, int r) {
    if (nxt[1][i][j] == 2) {
        if (nxt[1][i][j + 1] == 2) invert_direction(u, l, d, r);
        if (nxt[0][i][j + 1] == 2) {
            nxt[1][i][j] = 1, nxt[0][i][j + 1] = 3;
            nxt[1][i + 1][j + 1] = 3, nxt[0][i + 1][j] = 1;
            return true;
        }
    } else if (nxt[1][i][j] == 0) {
        if (nxt[1][i][j + 1] == 0) invert_direction(u, l, d, r);
        if (nxt[0][i][j + 1] == 0) {
            nxt[1][i][j] = 1, nxt[0][i][j + 1] = 3;
            nxt[1][i - 1][j + 1] = 3, nxt[0][i - 1][j] = 1;
            return true;
        }
    }
    return false;
}

bool add_bot(int i, int j, int u, int l, int d, int r) {
    if (nxt[1][i][j] == 1) {
        if (nxt[1][i + 1][j] == 1) invert_direction(u, l, d, r);
        if (nxt[0][i + 1][j] == 1) {
            nxt[1][i][j] = 2, nxt[0][i + 1][j] = 0;
            nxt[0][i][j + 1] = 2, nxt[1][i + 1][j + 1] = 0;
            return true;
        }
    } else if (nxt[1][i][j] == 3) {
        if (nxt[1][i + 1][j] == 3) invert_direction(u, l, d, r);
        if (nxt[0][i + 1][j] == 3) {
            nxt[1][i][j] = 2, nxt[0][i + 1][j] = 0;
            nxt[1][i + 1][j - 1] = 0, nxt[0][i][j - 1] = 2;
            return true;
        }
    }
    return false;
}

bool add_top(int i, int j, int u, int l, int d, int r) {
    if (nxt[1][i][j] == 1) {
        if (nxt[1][i - 1][j] == 1) invert_direction(u, l, d, r);
        if (nxt[0][i - 1][j] == 1) {
            nxt[1][i][j] = 0, nxt[0][i - 1][j] = 2;
            nxt[0][i][j + 1] = 0, nxt[1][i - 1][j + 1] = 2;
            return true;
        }
    } else if (nxt[1][i][j] == 3) {
        if (nxt[1][i - 1][j] == 3) invert_direction(u, l, d, r);
        if (nxt[0][i - 1][j] == 3) {
            nxt[1][i][j] = 0, nxt[0][i - 1][j] = 2;
            nxt[1][i - 1][j - 1] = 2, nxt[0][i][j - 1] = 0;
            return true;
        }
    }
    return false;
}

bool gen(int l, int r, int u, int d, int i, int j, int step = 1) {
    if (i < u || i > d || j < l || j > r || used[i][j] == 1) return false;
    if (step == (r - l + 1) * (d - u + 1) && used[i][j] == 533) return true;
    if (step == (r - l + 1) * (d - u + 1) || used[i][j] == 533) return false;
    used[i][j] = 1;
    for (int dir = 0; dir < 4; ++dir) {
        auto [di, dj] = shift[dir];
        int tmp = dir ^ 2;
        nxt[1][i][j] = dir;
        swap(nxt[0][i + di][j + dj], tmp);
        if (gen(l, r, u, d, i + di, j + dj, step + 1)) return true;
        swap(nxt[0][i + di][j + dj], tmp);
    }
    used[i][j] = 0;
    return false;
}

void build_path(int l, int r, int u, int d, int i1, int j1, int i2, int j2) {
    used[i2][j2] = 533;
    expect(gen(l, r, u, d, i1, j1), "gen path does not exist");
    used[i2][j2] = 532;
}

void solve() {
    int n, m, i1, j1, i2, j2;
    cin >> n >> m >> i1 >> j1 >> i2 >> j2;
    bool ok = exists_path(n, m, i1, j1, i2, j2);
    cout << (ok ? "YES\n" : "NO\n");
    if (!ok) return;


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            nxt[0][i][j] = nxt[1][i][j] = -1;
            used[i][j] = 0;
            painted[i][j] = true;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            painted[i][j] = false;
        }
    }
    bool swap_points = j1 > j2;
    if (swap_points) swap(j1, j2), swap(i1, i2);
    painted[i1][j1] = true;

    /* finding l, r */
    int l = 0;
    for (int x = j1 - 1; x > 0; --x) {
        if (exists_cycle(n, x) && exists_path(n, m - x, i1, j1 - x, i2, j2 - x)) {
            l = x;
            break;
        }
    }
    int r = m;
    for (int x = j2; x < m; ++x) {
        if (exists_cycle(n, m - x) && exists_path(n, x - l, i1, j1 - l, i2, j2 - l)) {
            r = x;
            break;
        }
    }
    build_trivial_cycle(1, 1, n, l, true);
    build_trivial_cycle(1, r + 1, n, m, false);
    /* filling from left */
    int lb = l;
    int ii = i1, jj = j1;
    if (r - l > 4) {
        bool cont = true;
        if (j1 == l + 2) {
            if (exists_path(n, r - j1, i1 - 1, 1, i2, j2 - j1)) {
                while (move(ii, jj, 2));
                assert(move(ii, jj, 3));
                while (move(ii, jj, 0));
                assert(move(ii, jj, 1));
                while (move(ii, jj, 2));
                assert(move(ii, jj, 1));
            } else if (exists_path(n, r - j1, i1 + 1, 1, i2, j2 - j1)) {
                while (move(ii, jj, 0));
                assert(move(ii, jj, 3));
                while (move(ii, jj, 2));
                assert(move(ii, jj, 1));
                while (move(ii, jj, 0));
                assert(move(ii, jj, 1));
            } else {
                cont = false;
            }
        }
        while (cont && jj < j2 - 1) {
            if (ii == 1) {
                if (exists_path(n, r - jj, n, 1, i2, j2 - jj)) {
                    while (move(ii, jj, 2));
                    assert(move(ii, jj, 1));
                } else {
                    cont = false;
                }
            } else if (ii == n) {
                if (exists_path(n, r - jj, 1, 1, i2, j2 - jj)) {
                    while (move(ii, jj, 0));
                    assert(move(ii, jj, 1));
                } else {
                    cont = false;
                }
            } else if (n - ii != 1 && exists_path(n, r - jj - 1, ii + 2, 1, i2, j2 - jj - 1)) {
                while (move(ii, jj, 0));
                assert(move(ii, jj, 1));
                while (!move(ii, jj, 3)) assert(move(ii, jj, 2));
                while (move(ii, jj, 2));
                assert(move(ii, jj, 1));
                while (move(ii, jj, 0));
                assert(move(ii, jj, 1));
            } else if (ii - 1 != 1 && exists_path(n, r - jj - 1, ii - 2, 1, i2, j2 - jj - 1)) {
                while (move(ii, jj, 2));
                assert(move(ii, jj, 1));
                while (!move(ii, jj, 3)) assert(move(ii, jj, 0));
                while (move(ii, jj, 0));
                assert(move(ii, jj, 1));
                while (move(ii, jj, 2));
                assert(move(ii, jj, 1));
            } else {
                cont = false;
            }
        }
        if (painted[ii][jj - 1]) lb = jj - 1;
    }
    int top = 0, bot = n;
    for (int i = n - 1; i >= max(ii, i2); --i) {
        if (exists_cycle(n - i, r - lb) && exists_path(i, r - lb, ii, jj - lb, i2, j2 - lb)) {
            bot = i;
        }
    }
    for (int i = 1; i < min(ii, i2); ++i) {
        if (exists_cycle(i, r - lb) && exists_path(bot - i, r - lb, ii - i, jj - lb, i2 - i, j2 - lb)) {
            top = i;
        }
    }
    build_trivial_cycle(1, lb + 1, top, r, true);
    build_trivial_cycle(bot + 1, lb + 1, n, r, true);
//    build_path(lb + 1, r, top + 1, bot, ii, jj, i2, j2);
    if (bot - top > 4) {
        int rev = ii <= i2 ? 0 : 1;
        if (rev) {
            painted[i2][j2] = true;
            painted[ii][jj] = false;
        }
        int i, j, ix, jx;
        if (ii <= i2) i = ii, j = jj, ix = i2, jx = j2;
        else i = i2, j = j2, ix = ii, jx = jj;
        bool cont2 = true;
        /* filling from top */
        if (i == top + 2) {
            if (exists_path(bot - i, r - lb, 1, j + 1 - lb, ix - i, jx - lb)) {
                while (move(i, j, 3, rev));
                assert(move(i, j, 0, rev));
                while (move(i, j, 1, rev));
                assert(move(i, j, 2, rev));
                while (move(i, j, 3, rev));
                assert(move(i, j, 2, rev));
            } else if (exists_path(bot - i, r - lb, 1, j - 1 - lb, ix - i, jx - lb)) {
                while (move(i, j, 1, rev));
                assert(move(i, j, 0, rev));
                while (move(i, j, 3, rev));
                assert(move(i, j, 2, rev));
                while (move(i, j, 1, rev));
                assert(move(i, j, 2, rev));
            } else {
                cont2 = false;
            }
        }
        while (cont2 && i < ix - 1) {
            if (j == lb + 1) {
                if (exists_path(bot - i, r - lb, 1, r - lb, ix - i, jx - lb)) {
                    while (move(i, j, 1, rev));
                    assert(move(i, j, 2, rev));
                } else {
                    cont2 = false;
                }
            } else if (j == r) {
                if (exists_path(bot - i, r - lb, 1, 1, ix - i, jx - lb)) {
                    while (move(i, j, 3, rev));
                    assert(move(i, j, 2, rev));
                } else {
                    cont2 = false;
                }
            } else if (r - j >= 2 && exists_path(bot - i - 1, r - lb, 1, j + 2 - lb, ix - i - 1, jx - lb)) {
                while (move(i, j, 3, rev));
                assert(move(i, j, 2, rev));
                while (!move(i, j, 0, rev)) move(i, j, 1, rev);
                while (move(i, j, 1, rev));
                assert(move(i, j, 2, rev));
                while (move(i, j, 3, rev));
                assert(move(i, j, 2, rev));
            } else if (j - lb > 2 && exists_path(bot - i - 1, r - lb, 1, j - 2 - lb, ix - i - 1, jx - lb)) {
                while (move(i, j, 1, rev));
                assert(move(i, j, 2, rev));
                while (!move(i, j, 0, rev)) move(i, j, 3, rev);
                while (move(i, j, 3, rev));
                assert(move(i, j, 2, rev));
                while (move(i, j, 1, rev));
                assert(move(i, j, 2, rev));
            } else {
                cont2 = false;
            }
        }
        int tp = painted[i - 1][j] ? i : i - 1;
        if (rev) {
            build_path(lb + 1, r, tp, bot, ix, jx, i, j);
        } else {
            build_path(lb + 1, r, tp, bot, i, j, ix, jx);
        }
    } else {
        build_path(lb + 1, r, top + 1, bot, ii, jj, i2, j2);
    }

    bool left_cycle = l == 0, right_cycle = r == m, top_cycle = top == 0, bot_cycle = bot == n;
    for (int i = i1, j = j1; nxt[1][i][j] != -1; ) {
        if (!left_cycle && j == l + 1) {
            left_cycle = add_left(i, j, 1, 1, n, l);
        }
        if (!right_cycle && j == r) {
            right_cycle = add_right(i, j, 1, r + 1, n, m);
        }
        if (!top_cycle && i == top + 1 && j > lb && j <= r) {
            top_cycle = add_top(i, j, 1, lb + 1, top, r);
        }
        if (!top_cycle && j == lb && i <= top) {
            top_cycle = add_right(i, j, 1, lb + 1, top, r);
        }
        if (!top_cycle && j == r + 1 && i <= top) {
            top_cycle = add_left(i, j, 1, lb + 1, top, r);
        }
        if (!bot_cycle && i == bot && j > lb && j <= r) {
            bot_cycle = add_bot(i, j, bot + 1, lb + 1, n, r);
        }
        if (!bot_cycle && j == lb && i > bot) {
            bot_cycle = add_right(i, j, bot + 1, lb + 1, n, r);
        }
        if (!bot_cycle && j == r + 1 && i > bot) {
            bot_cycle = add_left(i, j, bot + 1, lb + 1, n, r);
        }

        auto [di, dj] = shift[nxt[1][i][j]];
        i += di, j += dj;
    }
    expect(left_cycle && right_cycle && top_cycle && bot_cycle, "not all cycles were connected 2");
    /* get answer */
    string ans;
    if (swap_points) invert_direction(1, 1, n, m);
    for (int i = swap_points ? i2 : i1, j = swap_points ? j2 : j1; nxt[1][i][j] != -1; ) {
        ans += dir_to_char(nxt[1][i][j]);
        auto [di, dj] = shift[nxt[1][i][j]];
        i += di, j += dj;
    }
    ans += '\n';
    assert(sz(ans) == n * m);
    cout << ans;
//    print_path(1, 1, n, m);
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt;
    cin >> tt;
    for (int i = 0; i < tt; ++i) {
//        cerr << i + 1 << ' ';
        solve();
    }
    return 0;
}
