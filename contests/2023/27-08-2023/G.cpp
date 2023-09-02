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

#define tcT template<class T

using ll = long long;
using ld = long double;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;

#define mp  make_pair
#define F   first
#define S   second

#define sz(x)   int((x).size())
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

#define lb lower_bound
#define ub upper_bound

const int MOD = (int)1e9 + 7;   // 998244353;
const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < sz(v); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

ll give(ll r, ll s, string option) {
    assert(option == "+" || option == "-" || option == "*");
    if(option == "+") {
        return r + s;
    } else if(option == "-") {
        return r - s;
    } else {
        return r * s;
    }
}

void solve() {
    const int n = 5;
    const ll target = 23LL;
    vector<ll> X(n);
    for(auto& x: X)
        cin >> x;

    sor(X);
    vector<string> options = {"+", "-", "*"};
    bool ok = false;
    do {
        for(int a = 0; a < 3; a++) {
            ll partial1 = give(X[0], X[1], options[a]);
            for(int b = 0; b < 3; b++) {
                ll partial2 = give(partial1, X[2], options[b]);
                for(int c = 0; c < 3; c++) {
                    ll partial3 = give(partial2, X[3], options[c]);
                    for(int d = 0; d < 3; d++) {
                        ll partial4 = give(partial3, X[4], options[d]);
                        ok |= (partial4 == target);
                    }
                }
            }
        }
        // if(ok) break;
    } while(next_permutation(all(X)));
    cout << (ok?"Posible":"Imposible") << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
