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
    ll n;
    cin >> n;

    string s;
    cin >> s;
    for(auto& c: s) c = tolower(c);

    char target[4] = {'m', 'e', 'o', 'w'};
    int current = 0;
    bool ok = s[0] == target[0] && n >= 4;
    for(int i = 0; i < n; i++) {
        char c = s[i];
        if(c != target[current]) {
            if(current == 3) {
                ok = false;
                break;
            } else {
                current++;
                if(c != target[current]) {
                    ok = false;
                    break;
                }
            }
        }
    }
    ok &= current == 3;

    cout << (ok?"YES":"NO") << nl;
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
