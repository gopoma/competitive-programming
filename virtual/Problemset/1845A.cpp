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
    ll n, k, x;
    cin >> n >> k >> x;
    assert(1 <= x && x <= k && k <= n && n <= 100);

    if(x != 1) {
        cout << "YES\n";
        cout << n << nl;
        for(ll i = 0; i < n; i++)
            cout << "1 ";
        cout << nl;
    } else {
        // x = 1
        if(k==1 || (k==2 && n%2 != 0)) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            cout << (n/2) << nl;

            if(n%2!=0) {
                cout << "3 ";
                n -= 3;
            }
            for(ll i = 0; i < n; i+=2)
                cout << "2 ";
            cout << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
