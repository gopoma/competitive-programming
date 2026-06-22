#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define F first
#define S second
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

template <typename T>
istream& operator >>(istream &is, vector<T>& v) {
    int n;
    is >> n;
    v.resize(n);
    forn(i,n)
        is >> v[i];
    return is;
}

const char nl = '\n';

void solve() {
    int n;
    cin >> n;
    int h[n], a[n];

    forn(i, n) {
        cin >> h[i] >> a[i];
    }

    sort(a, a + n);

    int result = 0;
    for(int i = 0; i < n; i++) {
        auto k = lower_bound(a, a + n, h[i]) - a;
        if (k < n && a[k] == h[i]) {
            // auto l = lower_bound(a, a + n, h[i]);
            // auto u = upper_bound(a, a + n, h[i]);
            // result += u - l;
            auto r = equal_range(a, a + n, h[i]);
            result += r.S - r.F;
        }
    }

    cout << result << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
