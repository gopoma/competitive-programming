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

bool check(char a, char b, char x, char y) {
    return (a == x && b == y) || (a == y && b == x);
}

void solve() {
    ll N;
    cin >> N;

    string s1, s2;
    cin >> s1 >> s2;

    bool ok = true;
    for(ll i = 0; i < SIZE(s1); i++) {
        if(s1[i] != s2[i] && !check(s1[i], s2[i], '1', 'l') && !check(s1[i], s2[i], '0', 'o')) {
            ok = false;
            break;
        }
    }
    cout << (ok?"Yes":"No") << nl;
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
