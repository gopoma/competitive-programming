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

ll sum(vector<ll>& v) {
    ll res = 0LL;
    for(auto& e: v) {
        res += e;
    }
    return res;
}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> A(n), B(m);
    for(auto& e: A) cin >> e;
    for(auto& e: B) cin >> e;

    ll sumA = 0LL, sumB = 0LL;
    for(auto& e: A) sumA += e;
    for(auto& e: A) sumB += e;

    sort(A.begin(), A.end());
    sort(B.rbegin(), B.rend());
    assert(sz(A) >= 1 && sz(B) >= 1);
    if(A[0] < B[0]) {
        ll Atarget = A[0];
        ll Btarget = B[0];
        A.erase(A.begin());
        A.push_back(Btarget);

        B.erase(B.begin());
        B.push_back(Atarget);
    }
    // DBG3(A, B, k);

    if(k == 1LL) {
        ll ans = sum(A);
        cout << ans << n_l;
        return;
    }

    sort(A.begin(), A.end());
    sort(B.rbegin(), B.rend());
    assert(sz(A) >= 1 && sz(B) >= 1);
    if(A[n - 1] > B[m - 1]) {
        ll Atarget = A[n - 1];
        ll Btarget = B[m - 1];
        A.erase(A.begin() + n - 1);
        A.push_back(Btarget);

        B.erase(B.begin() + m - 1);
        B.push_back(Atarget);
    }

    if(k % 2 == 0) {
        ll ans = sum(A);
        cout << ans << n_l;
        return;
    }

    sort(A.begin(), A.end());
    sort(B.rbegin(), B.rend());
    assert(sz(A) >= 1 && sz(B) >= 1);
    if(A[0] < B[0]) {
        ll Atarget = A[0];
        ll Btarget = B[0];
        A.erase(A.begin());
        A.push_back(Btarget);

        B.erase(B.begin());
        B.push_back(Atarget);
    }

    ll ans = sum(A);
    cout << ans << n_l;
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
