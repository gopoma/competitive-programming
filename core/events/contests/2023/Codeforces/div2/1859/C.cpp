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
#define f   first
#define s   second

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

ll calc(vector<int>& v) {
    ll result = 0LL, partial = LLONG_MIN;
    for(int i = 0; i < sz(v); i++) {
        result += (i+1)*v[i];
        partial = max(partial, (ll)(i+1)*v[i]);
    }

    return (result - partial);
}

void brute(int n) {
    vector<int> perm(n);
    for(int i = 0; i < n; i++)
        perm[i] = i + 1;

    ll maxScore = LLONG_MIN;
    do {
        ll score = calc(perm);
        maxScore = max(maxScore, score);
    } while(next_permutation(all(perm)));

    for(int i = 0; i < n; i++)
        perm[i] = i + 1;
    do {
        ll score = calc(perm);
        if(score == maxScore) {
            DBG(perm);
        }
    } while(next_permutation(all(perm)));
}

void solve() {
    int n;
    cin >> n;
    assert(2 <= n && n <= 250);

    // brute(n);
    if(n == 2) {
        cout << "2\n";
        return;
    }

    ll ans = LLONG_MIN;
    for(int cp = 1; cp <= n; cp++) {
        vector<int> tmp(n);
        int current = 1;
        for(; current <= n && current <= cp; current++)
            tmp[current-1] = current;

        for(int aux = 0; current <= n; aux++, current++) {
            tmp[current-1] = n-aux;
        }

        ans = max(ans, calc(tmp));
    }
    cout << ans << n_l;
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
