#include <bits/stdc++.h>
using namespace std;

//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A>
string to_string(A v);

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "[";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "]";
    return res;
}
//* /Debugger

using ll = long long;
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

#define dbg(x) 42
#define GA dbg(0)
#define RAYA   dbg("================================");

//* Template
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

/**
 * Description: Tests primality up to $SZ$. Runs faster if only
 	* odd indices are stored.
 * Time: O(SZ\log\log SZ) or O(SZ)
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/primesieve
 */

 template<int SZ> struct Sieve {
	bitset<SZ> is_prime; vector<int> primes;
	Sieve() {
		is_prime.set(); is_prime[0] = is_prime[1] = 0;
		for (int i = 4; i < SZ; i += 2) is_prime[i] = 0;
		for (int i = 3; i*i < SZ; i += 2) if (is_prime[i])
			for (int j = i*i; j < SZ; j += i*2) is_prime[j] = 0;
		F0R(i,SZ) if (is_prime[i]) primes.push_back(i);
	}
	// int sp[SZ]{}; // smallest prime that divides
	// Sieve() { // above is faster
	// 	FOR(i,2,SZ) {
	// 		if (sp[i] == 0) sp[i] = i, primes.pb(i);
	// 		for (int p: primes) {
	// 			if (p > sp[i] || i*p >= SZ) break;
	// 			sp[i*p] = p;
	// 		}
	// 	}
	// }
};
//* /Template

Sieve<int(6e6)> st;

void solve() {
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    dbg(n);
    dbg(a);

    sort(a.rbegin(), a.rend());
    dbg(a);

    ll left  = 1; // always good
    ll right = n + 1; // always bad

    while(left + 1 < right) {
        ll middle = (left + right) >> 1LL;

        ll tot = 0;
        for(int i = 0; i < middle; i++) {
            tot += a[i] - 2LL;
        }

        bool ok = true;
        for(int i = 0; i < middle; i++) {
            ll take = st.primes[i] - 2LL;
            tot -= take;
            if(tot < 0) {
                ok = false;
                break;
            }
        }

        if(ok) left = middle;
        else right = middle;
    }

    ll response = n - left;
    cout << response << "\n";
}

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    assert(sz(st.primes) >= int(4e5) + 5);

    int t; cin >> t;
    while(t--) {
        solve();
        RAYA;
    }
}
