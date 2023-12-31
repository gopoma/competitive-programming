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
    ll n, k;
    cin >> n >> k;

    ll C[n];
    for(auto& c: C)
        cin >> c;

    ll count = 0;
    bool ok;
    if(C[0] == C[n-1]) {
        for(auto& c: C)
            count += (c == C[0]);
        
        ok = (count >= k);
    } else {
        ll go = -1;
        for(ll i = 0; i < n; i++) {
            count += (C[i] == C[0]);
            if(count == k) {
                go = i+1;
                break;
            }
        }

        if(go == -1) {
            cout << "NO" << nl;        
            return;
        }
        count=0;
        for(ll i = go; i < n; i++) {
            count += (C[i] == C[n-1]);
            if(count == k) {
                ok = true;
                break;
            }
        }
    }

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
