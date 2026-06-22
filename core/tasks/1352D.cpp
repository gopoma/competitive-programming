// sometimes pragmas don't work
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

#define sz(x)   int((x).size())
#define all(x)  x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define ins     insert
#define pb      push_back
#define eb      emplace_back

const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < int(v.size()); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

void solve() {
    int n;
    cin >> n;

    vector<ll> A(n);
    for(auto& e: A) {
        cin >> e;
    }

    bool turn = true; // true -> Alice | false -> Bob
    int moves = 0;
    ll current = 0LL, a = 0LL, b = 0LL;

    int left = 0, right = n - 1;
    while(left <= right) {
        ll acc = 0LL;

        if(turn) { // Alice
            while(left <= right && acc <= current) {
                acc += A[left];
                left++;
            }

            a += acc;
        } else { // Bob
            while(right >= left && acc <= current) {
                acc += A[right];
                right--;
            }

            b += acc;
        }

        current = acc;

        moves++;
        turn = !turn;
    }

    ll sum = accumulate(all(A), 0LL);
    assert(sum == a + b);

    cout << moves << " " << a << " " << b << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
