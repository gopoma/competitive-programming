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

// Function to find the length of the largest subarray
// having a sum at most k.
ll xd(vector<ll>& v, ll target) {
    ll n = v.size();
    ll s = 0;
    ll ans = 0;
    vector<ll> T(n);

    for(ll  i = 0LL; i < n;i++){
        s+=v[i];
        if(s <= target)  ans = i + 1;
        else {
           // need s - T[k] <= target
           // T[k] >= s-target
           while(i - ans > 0LL && T[i - ans - 1LL] >= s - target)  ans++;
        }

        if(i == 0LL) T[i] = s;
        else    T[i] = max(T[i - 1LL],s);
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    ll k; cin >> k;

    vector<ll> A(n), H(n);
    for(auto& a: A) cin >> a;
    for(auto& h: H) cin >> h;

    vector<pair<int, int>> segments;
    int left = 0, right = 0;
    for(int i = 0; i < n - 1; i++) {
        if(H[i] % H[i + 1] == 0LL) {
            right++;
        } else {
            segments.emplace_back(make_pair(left, right));
            left = i + 1;
            right = i + 1;
        }
    }
    segments.emplace_back(make_pair(left, right));

    // DBG(A);
    // DBG(H);
    // for(auto& it: segments) {
    //     assert(it.first <= it.second);
    //     DBG2(it.first, it.second);
    // }

    ll global_ans = 0LL;
    for(auto& it: segments) {
        vector<ll> temp;
        for(int i = it.first; i <= it.second; i++) {
            temp.emplace_back(A[i]);
        }

        global_ans = max(global_ans, xd(temp, k));
    }
    cout << global_ans << n_l;
    // RAYA;
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
