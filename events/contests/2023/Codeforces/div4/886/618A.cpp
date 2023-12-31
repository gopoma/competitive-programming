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

#define F first
#define S second
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

void solve() {
    /*
        1: 1
        2: 1 1 -> 2
        3: 2 1
        4: 2 2 -> 3
        5: 3 1
        6: 3 2
        7: 3 2 1
        8: 3 2 2 -> 3 3 -> 4
        9: 4 1
        10: 4 2
        11: 4 2 1
        12: 4 3
        13: 4 3 1
        14: 4 3 2
        15: 4 3 2 1
        16: 4 3 2 2 -> 4 3 3 -> 4 4 -> 5
        17: 5 1
        18: 5 2
        19: 5 2 1
        20: 5 3
        21: 5 3 1
        22: 5 3 2
        23: 5 3 2 1
        24: 5 4
        25: 5 4 1
        26: 5 4 2
        27: 5 4 2 1
        28: 5 4 3
        29: 5 4 3 1
        30: 5 4 3 2
        31: 5 4 3 2 1
        32: 6
    */

    ll x;
    cin >> x;

    for (int i = 31; i >= 0; i--) {
        if (x&(1<<i)) cout << (i+1) << " ";
    }
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
