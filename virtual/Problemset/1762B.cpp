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

    ll A[n], B[n];
    for(auto& a: A) cin >> a;
    for(ll i = 0; i < n; i++) B[i] = A[i];

    sort(A, A + n);
    unordered_map<ll, ll> incs;
    for(ll i = 1; i < n; i++) {
        // A[i] A[i-1]
        ll inc, prev = A[i];
        if(A[i] % A[i-1] != 0) {
            inc = A[i-1] - (A[i] % A[i-1]);
            A[i] += inc;
        } else inc = 0;

        incs[prev] = inc;
    }

    cout << n << nl;
    for(ll i = 0; i < n; i++)
        cout << (i+1) << " " << incs[B[i]] << nl;
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
