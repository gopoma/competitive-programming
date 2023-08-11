#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

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
    int n; cin >> n;
    vector<int> p(n);

    for(int& pp: p) {
        cin >> pp;
    }

    int position1 = -1, position2 = -1, positionN = -1;
    for(int i = 0; i < n; i++) {
        if(p[i] == 1) {
            position1 = i;
        } else if(p[i] == 2) {
            position2 = i;
        } else if(p[i] == n) {
            positionN = i;
        }
    }

    if(position1 > position2) {
        swap(position1, position2);
    }

    if(positionN < position1) {
        cout << (positionN + 1) << " " << (position1 + 1) << "\n";
    } else if(position2 < positionN) {
        cout << (position2 + 1) << " " << (positionN + 1) << "\n";
    } else {
        cout << "1 1\n";
    }
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
