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

string fans = "";

void solve() {
    // RAYA;
    string s1;
    ll pos;
    cin >> s1 >> pos;

    const ll n = ll(sz(s1));

    ll target = (n * (n + 1LL)) / 2LL - pos + 1LL, block = -1LL;
    ll left = 1, right = n;
    while(left <= right) {
        ll middle = (left + right) / 2LL;

        ll bb = (middle * (middle + 1LL)) / 2LL;
        ll aa = bb - middle + 1;
        assert(aa <= bb);

        bool ok = aa <= target && target <= bb;
        if(ok) {
            block = middle;
            break;
        } else if(target < aa) {
            right = middle - 1LL;
        } else if(target > bb) {
            left = middle + 1LL;
        } else {
            assert(false);
        }
    }
    assert(block != -1LL);

    ll fref = 1LL + (n * (n + 1LL)) / 2LL - (block * (block + 1LL)) / 2LL;
    block = n - block + 1LL;
    // DBG3(n, block, fref);

    ll amount_to_remove = block - 1LL;

    ll fpos = pos - fref;

    //
    ll x = amount_to_remove;
    string fff = "";
    for (auto c: s1) {
        while (x > 0 && !fff.empty() && c < fff.back()) {
            fff.pop_back();
            x--;
        }
        fff += c;
    }
    //

    char ans = fff[fpos];
    fans += ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    cin >> t;

    while(t--)
        solve();

    cout << fans;

    return 0;
}
