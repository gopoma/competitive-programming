#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define DBG3(x,y,z) do {DBGY(x); DBGY(y); DBG(z); } while (false)
#define DBG4(x,y,z,w) do {DBGY(x); DBGY(y); DBGY(z); DBG(w); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

ll getDifferentTriplets(ll limit) {
    DBG(limit);
    ll amountDifferentTriplets = 0;

    for(ll i = 1; i < limit; i++) {
        for(ll j = i + 1; j < limit; j++) {
            if(i * i + j * j == limit * limit) {
                DBG3(i, j, limit);
                amountDifferentTriplets++;
            }
        }
    }

    return amountDifferentTriplets;
}

void solve() {
    ll a = 26, b = 26; // cin >> a >> b;
    a--; b--;

    ll pA, pB;
    pA = getDifferentTriplets(a);
    RAYA;
    RAYA;
    RAYA;
    pB = getDifferentTriplets(b);

    /*
    ll result;
    if(a == b) {
        result = 1 + 2 * pA;
    } else {
        result = 2 + 4 * pA * pB;
    }

    cout << result << nl;
    */
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;

    while(t--)
        solve();

    return 0;
}
