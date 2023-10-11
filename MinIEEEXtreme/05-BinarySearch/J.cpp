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

/* Returns true if s1 is subsequence of s2 */
bool is_subsequence(string& s1, string& s2) {
    int n = s1.length(), m = s2.length();
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (s1[i] == s2[j])
            i++;
        j++;
    }

    /* If i reaches end of s1,that mean we found all
    characters of s1 in s2,
    so s1 is subsequence of s2, else not */
    return i == n;
}

void solve() {
    string t, p;
    cin >> t >> p;

    assert(sz(p) < sz(t));
    const int n = sz(t);

    vector<int> a(n);
    for(auto& e: a) {
        cin >> e;
    }

    auto good = [&](int x) {
        assert(1 <= x && x <= n);

        set<int> deleted;
        for(int i = 0; i < x; i++) {
            deleted.ins(a[i] - 1);
        }

        string partial = "";
        for(int i = 0; i < n; i++) {
            if(deleted.find(i) == deleted.end()) {
                partial += t[i];
            }
        }

        return is_subsequence(p, partial);
    };

    int left = 0, right = n;
    // left is always good
    // right is always bad

    while(left + 1 < right) {
        int middle = (left + right) / 2;
        if(good(middle)) {
            left = middle;
        } else {
            right = middle;
        }
    }

    int ans = left;
    cout << ans << n_l;
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
