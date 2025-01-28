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

    ll w[n+1]{0}, sum = 0;
    for(ll i = 1; i <= n; i++) {
        cin >> w[i];
        sum += w[i];
    }

    if(sum % 2 != 0) {
        cout << "NO\n";
        // cout << "\nskipped!\n";
    } else {
        ll W = sum;
        bool possible[W+1]{false};
        possible[0] = true;
        for(ll k = 1; k <= n; k++) {
            for(ll x = W; x >= 0; x--) {
                if(possible[x]) possible[x+w[k]] = true;
            }

            /*
            cout << "W:\t";
            for(int i = 0; i <= W; i++)
                cout << i << " ";
            cout << nl;
            cout << "p?:\t";
            for(auto& p: possible)
                cout << p << " ";
            cout << nl;
            */
        }

        cout << ((possible[W/2])? "YES" : "NO") << nl;
    }
    // RAYA;
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
