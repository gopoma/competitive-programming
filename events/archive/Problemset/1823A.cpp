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

int xd(string a, string b, int m, int n) {
    if ((m == 0 && n == 0) || n == 0)
        return 1;

    if (m == 0)
        return 0;

    if (a[m - 1] == b[n - 1])
        return xd(a, b, m - 1, n - 1) +
               xd(a, b, m - 1, n);
    else
        return xd(a, b, m - 1, n);
}

void solve() {
    ll n, k;
    cin >> n >> k;

    for(ll ao = 0; ao <= n; ao++) {
        ll amo = n - ao;
        ll sum = (ao*(ao-1)/2) + (amo*(amo-1)/2);
        if(sum == k) {
            cout << "YES\n";
            for(ll i = 0; i < ao; i++)
                cout << "1 ";
            for(ll i = 0; i < amo; i++)
                cout << "-1 ";
            cout << nl;
            return;
        }
    }

    cout << "NO\n";
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
