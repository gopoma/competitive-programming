// sometimes pragmas don't work
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define tcT template<class T

using ll = long long;
using ld = long double;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;

#define sz(x)   int((x).size())
#define all(x)  bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define ins     insert
#define pb      push_back
#define eb      emplace_back

const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < sz(v); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

void solve() {
    int n;
    cin >> n;

    vector<vector<char>> a(n, vector<char>(n, '$'));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    ll ans = 0LL;
    const int N = sz(a);
    // Traverse each cycle
    for (int i = 0; i < N / 2; i++) {
        for (int j = i; j < N - i - 1; j++) {
            // Swap elements of each cycle
            // in clockwise direction

            // a[i][j], a[N - 1 - j][i], a[N - 1 - i][N - 1 - j], a[j][N - 1 - i]
            char local_max = max(a[i][j], max(a[N - 1 - j][i], max(a[N - 1 - i][N - 1 - j], a[j][N - 1 - i])));
            ans += ll(abs(local_max - a[i][j]));
            ans += ll(abs(local_max - a[N - 1 - j][i]));
            ans += ll(abs(local_max - a[N - 1 - i][N - 1 - j]));
            ans += ll(abs(local_max - a[j][N - 1 - i]));

            // int temp = a[i][j];
            // a[i][j] = a[N - 1 - j][i];
            // a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
            // a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
            // a[j][N - 1 - i] = temp;
        }
    }

    cout << ans << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
