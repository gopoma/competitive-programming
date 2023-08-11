#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define DBG3(x,y,z) do {DBGY(x); DBGY(y); DBG(z); } while (false)
#define DBG4(x,y,z,w) do {DBGY(x); DBGY(y); DBGY(z); DBG(w); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

void solve() {
    // <>
    ll n, k, q;
    cin >> n >> k >> q;

    vector<ll> s;
    for(ll i = 0; i < n; i++) {
        ll a;
        cin >> a;

        if(a <= q) {
            s.push_back(1);
        } else {
            s.push_back(0);
        }
    }

    vector<ll> lagoons;
    while(!s.empty()) {
        ll counter = 0;
        while(s.back() == 0) {
            s.pop_back();
        }

        if(s.empty()) {
            break;
        }

        while(s.back() == 1) {
            counter++;
            s.pop_back();
        }

        lagoons.push_back(counter);
    }

    ll result = 0;
    for(ll& l: lagoons) {
        // l k
        if(l < k) {
            continue;
        }
        const ll tot = l*l - (l*(l+1)/2) + l;
        const ll current = l*(k-1) - ((k-1)*(k)/2) + (k-1);
        result += tot - current;
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
