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

void solve() {
    int n;
    cin >> n;

    int k1;
    cin >> k1;
    deque<int> A;
    for(int i = 0; i < k1; i++) { int a; cin >> a; A.push_back(a); }


    int k2;
    cin >> k2;
    deque<int> B;
    for(int i = 0; i < k2; i++) { int b; cin >> b; B.push_back(b); }

    assert(k1 + k2 == n);
    assert(k1 != n && k2 != n);

    // const int upper_bound = 4000000;
    set<pair<deque<int>, deque<int>>> partials;
    int count = 1;
    while(true) {
        int a_in_game = A.front(); A.pop_front();
        int b_in_game = B.front(); B.pop_front();

        assert(a_in_game != b_in_game);
        if(a_in_game > b_in_game) {
            A.push_back(b_in_game);
            A.push_back(a_in_game);
        } else {
            B.push_back(a_in_game);
            B.push_back(b_in_game);
        }

        if(sz(A) == 0) {
            assert(sz(B) == n);
            cout << count << " 2\n";
            return;
        } else if(sz(B) == 0) {
            assert(sz(A) == n);
            cout << count << " 1\n";
            return;
        }

        if(partials.count(mp(A, B))) {
            cout << "-1\n";
            return;
        } else {
            partials.ins(mp(A, B));
        }

        count++;
    }
    assert(false);

    // if(count == upper_bound) {
    //     cout << "-1\n";
    // }
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
