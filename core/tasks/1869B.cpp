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

ll distance(pair<ll, ll> A, pair<ll, ll> B) {
    return abs(A.first - B.first) + abs(A.second - B.second);
}

void solve() {
    // RAYA;
    ll n, k, a, b;
    cin >> n >> k >> a >> b; a--; b--;
    assert(2LL <= n);

    vector<pair<ll, ll>> C(n);
    for(auto& e: C) {
        cin >> e.first >> e.second;
    }

    ll ans = -1LL;
    if(max(a, b) < k) {
        ans = 0LL;
    } else {
        pair<ll, ll> origin = C[a];
        pair<ll, ll> destiny = C[b];

        ans = distance(origin, destiny);

        if(a < k) {
            if(k > 1) {
                for(ll i = 0LL; i < k; i++) {
                    if(i != a) {
                        ans = min(ans, distance(C[i], destiny));
                    }
                }
            }
        } else if(b < k) {
            if(k > 1) {
                for(ll i = 0LL; i < k; i++) {
                    if(i != b) {
                        ans = min(ans, distance(C[i], origin));
                    }
                }
            }
        } else {
            assert(a >= k && b >= k);
            if(k >= 2) {
                ll indexOriginCandidate = -1, minDistance = LLONG_MAX;
                for(ll i = 0; i < k; i++) {
                    if(distance(origin, C[i]) < minDistance) {
                        minDistance = distance(origin, C[i]);
                        indexOriginCandidate = i;
                    }
                }
                assert(indexOriginCandidate != -1LL);

                ll indexDestinyCandidate = -1;
                minDistance = LLONG_MAX;
                for(ll i = 0; i < k; i++) {
                    if(i == indexOriginCandidate) continue;

                    if(distance(destiny, C[i]) < minDistance) {
                        minDistance = distance(destiny, C[i]);
                        indexDestinyCandidate = i;
                    }
                }
                assert(indexDestinyCandidate != -1LL);

                // DBG2(origin.first, origin.second);
                // DBG2(destiny.first, destiny.second);
                // DBG2(C[indexOriginCandidate].first, C[indexOriginCandidate].second);
                // DBG2(C[indexDestinyCandidate].first, C[indexDestinyCandidate].second);
                ans = min(ans, distance(origin, C[indexOriginCandidate]) + distance(destiny, C[indexDestinyCandidate]));
            }
        }
    }
    assert(ans != -1LL);
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
