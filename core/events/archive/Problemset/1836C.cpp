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

int getAmountDigits(ll num) {
    return SIZE(to_string(num));
}

void solve() {
    for(ll A = 1; A < 5; A++) {
        for(ll B = 1; B < 5; B++) {
            for(ll C = 1; C < 5; C++) {
                ll count = 0;
                for(ll a = pow(10, A-1); a < pow(10, A); a++) {
                    for(ll b = pow(10, B-1); b < pow(10, B); b++) {
                        if(getAmountDigits(a+b) == C) {
                            count++;
                        }
                    }
                }
                bool possible = (pow(10, A)-1+pow(10, B)-1)>=pow(10, C-1);
                DBG3(A, B, C);
                DBG2(possible, count);
                RAYA;
            }
        }
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
