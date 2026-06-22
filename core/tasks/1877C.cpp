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
    ll n, m, k;
    cin >> n >> m >> k;

    assert(1LL <= n);
    assert(0LL <= m);
    assert(1LL <= k && k <= n + 1LL);

    ll ans;
    if(k >= 4LL) {
        ans = 0LL;
    } else if(k == 1LL) {
        ans = 1LL;
    } else if(k == 2LL && (1LL <= m)) {
        if(n < m) {
            ans = (m / n) + (n - 1);
        } else {
            // n >= m
            ans = m;
        }
    } else if(k == 3LL && (n < m)) {
        ans = m - (m / n) - (n - 1);
    } else {
        ans = 0LL;
    }

    cout << ans << n_l;
    // DBG4(n, m, k, ans);

    // for(ll i = 0LL; i <= m; i++) {
    //     vector<ll> SS(n + 1LL);
    //     SS[n] = i;
    //     for(ll j = n - 1; j >= 0; j--) {
    //         SS[j] = SS[j + 1LL] % (j + 1LL);
    //     }
    //     DBG2(i, SS);
    // }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
