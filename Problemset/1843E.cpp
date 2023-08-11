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
    ll m, n;
    cin >> m >> n;

    vector<pair<ll, ll>> segments(n);
    for(auto& it: segments)
        cin >> it.F >> it.S;



    ll q;
    cin >> q;

    ll X[q];
    for(auto& x: X) cin >> x;


    ll left=0, right=q-1, result = -1;
    while(left <= right) {
        ll middle = left + (right-left)/2;

        ll A[m+1]{0}, dp[m+1]{0};
        for(ll k = 0; k <= middle; k++)
            A[X[k]] = 1;
        for(ll k = 1; k <= m; k++)
            dp[k] = dp[k-1] + A[k];



        bool found = false;
        for(auto& it: segments) {
            if((2*(dp[it.S]-dp[it.F-1])) > (it.S-it.F+1)) {
                result = middle + 1;
                found = true;
                break;
            }
        }


        if(!found) {
            left = middle+1;
        } else {
            right = middle-1;
        }
    }

    cout << result << nl;
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
