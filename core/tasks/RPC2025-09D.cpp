#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using db = long double;

// #define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0
#define RAYA dbg("===========================")

db p, r, y;
db f(db n) {
    db s = n - r;
    db e = (p + y - n - s) / db(2);
    db w = e - p;

    db mx = max({fabsl(n), fabsl(s), fabsl(e), fabsl(w)});
    return -mx;
}

db ternary_search(db l, db r) {
    db eps = 1e-9;
    for(int _ = 0; _ < 200; _++) {
        db m1 = l + (r - l) / db(3);
        db m2 = r - (r - l) / db(3);
        db f1 = f(m1);
        db f2 = f(m2);
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return l;
}

const db EPS = db(1e-9);
bool eq(db x, db y) {
    return fabsl(x - y) < EPS;
}

void solve() {
    cin >> p >> r >> y;

    db n = ternary_search(db(-1), db(+1));
    db s = n - r;
    db e = (p + y - n - s) / db(2);
    db w = e - p;

    cout << n << " " << e << " " << s << " " << w << "\n";

    db mx = max({fabsl(n), fabsl(s), fabsl(e), fabsl(w)});
    dbg(p);
    dbg(e - w);
    assert(eq(p, e - w));
    assert(eq(r, n - s));
    assert(eq(y, n + e + s + w));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(12);

    int t; cin >> t;

    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        solve();
    }

    return 0;
}
