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

bool is_integer(ld k) {
  return ceil(k) == k;
}

void solve() {
    ll n, k;
    cin >> n >> k;

    if(k >= 50) {
        cout << "0\n";
        return;
    }

    vector<pair<ll, ll>> gen;
    gen.push_back({1, 0});
    gen.push_back({0, 1});
    gen.push_back({1, 1});

    for(ll i = 3; i < k; i++) {
        gen.push_back({gen[i-1].F+gen[i-2].F, gen[i-1].S+gen[i-2].S });
    }

    pair<ll, ll> last = gen[SIZE(gen)-1];
    ll cofa = last.F;
    ll cofb = last.S;

    ll ans = 0;
    for(ll a = 0; a <= n; a++) {
        if((n-cofa*a) % cofb == 0) {
            ll b = (n-cofa*a)/cofb;
            if(b >= 0 && a <= b) {
                ans++;
            }
        }
    }
    cout << ans << nl;
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
