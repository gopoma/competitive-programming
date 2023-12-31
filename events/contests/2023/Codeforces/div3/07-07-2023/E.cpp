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

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

unordered_set<ll> possibles;
const ll MAXK = 1000000;
const ll MAXP = 59;
const ll MAXN = 1e18;

void precompute() {
    for(ll k = 2; k <= MAXK; k++) {
        ll val = 1 + k;
        ll acc = k * k;
        for(ll p = 2; p <= MAXP; p++) {
            val += acc;
            if(val > MAXN) break;
            possibles.insert(val);
            acc *= k;
        }
    }
}

void solve() {
    ll n;
    cin >> n;

    if(possibles.count(n)) {
        cout << "YES\n";
        return;
    } else {
        if(n <= 1000000) { cout << "NO\n"; return; }

        ld root = -1 + (ld)sqrt(1 - 4*(1 - (ld)n));
        root /= 2;

        if(root == floor(root)) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    startTime = clock();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    ll t;
    cin >> t;

    for(ll i = 1; i <= t; i++) {
        solve();

        // cerr << "--- Case #" << i << " end ---\n";
        // cerr << "time = " << getCurrentTime() << "s\n";
        // cerr << "++++++++++++++++++++\n";
    }

    return 0;
}
