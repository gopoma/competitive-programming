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

typedef unsigned long long ull;
typedef long long   ll;
typedef long double ld;

const char nl = '\n';

void solve() {
    ll N;
    cin >> N;

    if(N <= pow(10, 3))
        cout << N;
    else if(N < pow(10, 4))
        cout << (N/10) << "0";
    else if(N < pow(10, 5))
        cout << (N/100) << "00";
    else if(N < pow(10, 6))
        cout << (N/1000) << "000";
    else if(N < pow(10, 7))
        cout << (N/10000) << "0000";
    else if(N < pow(10, 8))
        cout << (N/100000) << "00000";
    else if(N < pow(10, 9))
        cout << (N/1000000) << "000000";
    cout << nl;
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
