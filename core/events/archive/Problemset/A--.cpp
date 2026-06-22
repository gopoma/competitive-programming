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
    // <>
    ll maxBailes = -1, maxComida = -1, maxCultura = -1;
    cin >> maxBailes >> maxComida >> maxCultura;
    assert(maxBailes >= 0);
    assert(maxComida >= 0);
    assert(maxCultura >= 0);
    vector<string> bailes, comida, cultura;

    ll c;
    while(cin >> c) {
        string tipo;
        cin >> tipo;

        string descripcion;
        cin.ignore();
        getline(cin, descripcion);

        if(tipo == "BAILES") {
            if(c > maxBailes) {continue;}
            maxBailes -= c;
            bailes.push_back(descripcion);
        } else if(tipo == "COMIDA") {
            if(c > maxComida) {continue;}
            maxComida -= c;
            comida.push_back(descripcion);
        } else {
            if(c > maxCultura) {continue;}
            maxBailes -= c;
            cultura.push_back(descripcion);
        }
    }

    cout << "BAILES" << nl;
    for(string& s: bailes) cout << s << nl;
    cout << "COMIDA" << nl;
    for(string& s: comida) cout << s << nl;
    cout << "CULTURA" << nl;
    for(string& s: cultura) cout << s;
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
