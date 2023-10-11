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

struct Assistant  {
    ll t;
    ll z;
    ll y;
};

void solve() {
    ll m, n;
    cin >> m >> n;

    vector<Assistant> v(n);
    for(auto& e: v) {
        cin >> e.t >> e.z >> e.y;
    }

    // How many balloons can the assistant inflate in x minutes?
    auto single = [&](ll x, Assistant s) {
        ll blocks = x / (s.t * s.z + s.y);
        ll rem = x - (blocks * (s.t * s.z + s.y));
        rem = min(rem, s.t * s.z);

        ll res = blocks * s.z + (rem / s.t);
        return res;
    };

    // x -> time
    auto ok = [&](ll x) {
        ll sum = 0LL;
        for(auto& e: v) {
            sum += single(x, e);
        }

        return (sum >= m);
    };

    // left is always bad
    // right is always ok
    ll left = 0LL, right = 1LL;
    while(!ok(right)) {
        right *= 2LL;
    }
    assert(right >= 0LL);

    while(left + 1 < right) {
        ll middle = (left + right) / 2LL;

        if(ok(middle)) {
            right = middle;
        } else {
            left = middle;
        }
    }

    ll min_time = right;
    vector<ll> ans(n);
    for(int i = 0; i < n; i++) {
        ans[i] = single(min_time, v[i]);
    }

    ll sum2 = accumulate(ans.begin(), ans.end(), 0LL);
    ll surplus = sum2 - m;
    assert(surplus >= 0LL);

    for(int i = 0; i < n; i++) {
        if(surplus >= ans[i]) {
            surplus -= ans[i];
            ans[i] = 0LL;
        } else {
            assert(surplus < ans[i]);
            ans[i] -= surplus;
            surplus = 0LL;
        }
    }

    ll sum3 = accumulate(ans.begin(), ans.end(), 0LL);
    assert(sum3 == m);

    cout << min_time << n_l;
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
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
