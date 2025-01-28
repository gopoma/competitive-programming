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
    string s;
    cin >> s;
    int n = SIZE(s);

    bool gonext = false;
    bool ok = false;
    for(int i = 0; i < n-1; i++) {
        if(!gonext && s[i] == 'A' && s[i+1] == 'B') {
            gonext = true;
            i++;
        } else if(gonext && s[i] == 'B' && s[i+1] == 'A') {
            ok = true;
            break;
        }
    }

    gonext = false;
    for(int i = 0; i < n-1; i++) {
        if(!gonext && s[i] == 'B' && s[i+1] == 'A') {
            gonext = true;
            i++;
        } else if(gonext && s[i] == 'A' && s[i+1] == 'B') {
            ok = true;
            break;
        }
    }

    cout << (ok?"YES":"NO") << nl;
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
