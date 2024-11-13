//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
 
using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f  first
#define s  second



#define tcT template <class T
#define tcTU tcT, class U

tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



// vectors
// oops size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()
#define ts to_string

#define lb lower_bound
#define ub upper_bound



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



//? Custom Helpers
template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

//? __builtin_popcountll
ll GetBit(ll mask, ll bit) { return (mask >> bit) & 1LL; }
void TurnOn(ll& mask, ll bit) { mask = mask | (1LL << bit); }
void TurnOff(ll& mask, ll bit) { mask = mask & (~(1LL << bit)); }

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0);

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
bool issubsequence(string s1, string s2) {
    int n = s1.length(), m = s2.length();
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (s1[i] == s2[j])
            i++;
        j++;
    }
    /*If i reaches end of s1,that mean we found all
    characters of s1 in s2,
    so s1 is subsequence of s2, else not*/
    return i == n;
}

//? /Template

bool check(str S) {
    vector<char> stk;
    each(c, S) {
        if(c == '(') {
            stk.emplace_back('(');
        } else {
            if(stk.empty()) return false;
            stk.pop_back();
        }
    }
    return stk.empty();
}

const int INF = int(1e9);
using Info = pair<int, str>;
str brute(int N, str S) {
    Info ans = mp(INF, "$");
    for(int size = N; size <= 2 * N; size++) {
        for(int mask = 0; mask < (1 << size); mask++) {
            str T;
            for(int i = 0; i < size; i++) {
                if(mask & (1 << i)) {
                    T.pb('(');
                } else {
                    T.pb(')');
                }
            }
            if(check(T) && issubsequence(S, T)) {
                ckmin(ans, mp(sz(T), T));
            }
        }
    }
    return ans.s;
}

using Answer = tuple<int, char, int, int>;
const Answer MAX = make_tuple(INF, '$', -1, -1);
bool vis[105][110];
Answer memo[105][110];
str slv(int N, str S) {
    //? <>
    memset(vis, false, sizeof(vis));
    auto dp = [&](const auto& dp, int i, int pref) -> Answer {
        if(pref > N + 5) return MAX;
        if(pref < 0) return MAX;

        if(i == N) {
            if(pref > 0) {
                if(vis[i][pref]) return memo[i][pref];
                vis[i][pref] = true;
                return memo[i][pref] = make_tuple(get<0>(dp(dp, i, pref - 1)) + 1, ')', i, pref - 1);
            }
            else return make_tuple(0, '$', -1, -1);
        }

        if(vis[i][pref]) return memo[i][pref];
        vis[i][pref] = true;

        Answer ans = MAX;
        
        ckmin(ans, make_tuple(get<0>(dp(dp, i, pref + 1)) + 1, '(', i, pref + 1));
        
        if(S[i] == '(') ckmin(ans, make_tuple(get<0>(dp(dp, i + 1, pref + 1)) + 1, '(', i + 1, pref + 1));
        else            ckmin(ans, make_tuple(get<0>(dp(dp, i + 1, pref - 1)) + 1, ')', i + 1, pref - 1));

        return memo[i][pref] = ans;
    };
    Answer ans = dp(dp, 0, 0);
    dbg(ans);
    str response;
    while(get<2>(ans) != -1) {
        response.pb(get<1>(ans));
        ans = dp(dp, get<2>(ans), get<3>(ans));
    }
    return response;
}

void solve() {
    int N; cin >> N;
    str S; cin >> S;

    str ans = slv(N, S);
    dbg(ans);
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;

        int N = rng_int(0, 8);
        str S;
        rep(N) {
            if(rng_int(0, 1)) S.pb('(');
            else S.pb(')');
        }
        dbg(N);
        dbg(S);
        dbg("Brute");
        str ans = brute(N, S);
        dbg("Brute");
        dbg("Greedy");
        str greedy = slv(N, S);
        dbg("/Greedy");
        dbg(ans);
        dbg(greedy);
        chk(ans == greedy);
    }

    int t = 1; //! cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        solve();
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
