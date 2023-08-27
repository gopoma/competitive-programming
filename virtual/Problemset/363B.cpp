#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

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

    vector<ll> v(n);
    for(ll& h: v) {
        cin >> h;
    }

    vector<ll> ps(n + 1);
    ps[0] = 0;
    for(ll i = 1; i < n + 1; i++) {
        ps[i] = ps[i - 1] + v[i - 1];
    }

    ll minSum = LLONG_MAX, j = -1;
    for(ll i = 1; i < n - k + 2; i++) {
        if(ps[i + k - 1] - ps[i - 1] < minSum) {
            minSum = ps[i + k - 1] - ps[i - 1];
            j = i;
        }
    }
    cout << j << "\n";
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
