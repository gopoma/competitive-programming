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

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

void solve() {
    ll n; cin >> n;
    vector<ll> pp;

    if(n % 2 != 0) {
        pp.push_back(3);
        n -= 3;
    }

    while(n != 0) {
        pp.push_back(2);
        n -= 2;
    }

    cout << SIZE(pp) << "\n";
    for(int i = 1; i < SIZE(pp); i++) {
        cout << pp[i] << " ";
    }
    cout << pp[0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;

    while(t--)
        solve();

    return 0;
}
