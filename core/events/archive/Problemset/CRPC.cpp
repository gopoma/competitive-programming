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

ll DEXOR(ll a, ll b) {
    return ((a <= 2 && b <= 2) || (a >= 7 && b >= 7))? 0 : 9;
}

void solve() {
    string a, b;
    cin >> a >> b;

    string result = "";
    for(ll i = 0; i < max(SIZE(a), SIZE(b)); i++) {
        ll d1 = 0, d2 = 0;
        if(i < SIZE(a)) {
            d1 = a[SIZE(a) - i - 1]-'0';
        }
        if(i < SIZE(b)) {
            d2 = b[SIZE(b) - i - 1]-'0';
        }

        result = to_string(DEXOR(d1, d2)) + result;
    }

    cout << result << nl;
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
