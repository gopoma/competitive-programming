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
    ll d=3;
    char field[d][d];

    for(ll i=0; i<d; i++)
        for(ll j=0; j<d; j++)
            cin >> field[i][j];

    bool Xw=false, Ow=false, Pw=false;
    for(ll i=0; i<d; i++) {
        bool Xtmp=true, Otmp=true, Ptmp=true;
        for(ll j=0; j<d; j++) {
            Xtmp &= field[i][j] == 'X';
            Otmp &= field[i][j] == 'O';
            Ptmp &= field[i][j] == '+';
        }
        Xw |= Xtmp;
        Ow |= Otmp;
        Pw |= Ptmp;

        Xtmp=true, Otmp=true, Ptmp=true;
        for(ll j=0; j<d; j++) {
            Xtmp &= field[j][i] == 'X';
            Otmp &= field[j][i] == 'O';
            Ptmp &= field[j][i] == '+';
        }
        Xw |= Xtmp;
        Ow |= Otmp;
        Pw |= Ptmp;
    }

    bool Xtmp=true, Otmp=true, Ptmp=true;
    for(ll k=0; k<d; k++) {
        Xtmp &= field[k][k] == 'X';
        Otmp &= field[k][k] == 'O';
        Ptmp &= field[k][k] == '+';
    }
    Xw |= Xtmp;
    Ow |= Otmp;
    Pw |= Ptmp;

    Xtmp=true, Otmp=true, Ptmp=true;
    for(ll k=0; k<d; k++) {
        Xtmp &= field[k][d-k-1] == 'X';
        Otmp &= field[k][d-k-1] == 'O';
        Ptmp &= field[k][d-k-1] == '+';
    }
    Xw |= Xtmp;
    Ow |= Otmp;
    Pw |= Ptmp;

    if(Xw) cout << "X\n";
    else if(Ow) cout << "O\n";
    else if(Pw) cout << "+\n";
    else cout << "DRAW\n";
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
