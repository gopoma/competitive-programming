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
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? /Template

str slv(str S) {
    ll n = sz(S);
    str ans;
    set<ll> idx;
    for(ll i = 0; i < n; i++) idx.emplace(i);
    for(ll i = 0; i < n;) {
        if(!idx.count(i)) {
            i++;
            continue;
        }
        auto it = idx.lower_bound(i);
        it++;
        int count = 0;
        
        pl current = mp(ll(S[i] - '0'), -i);
        bool could = false;
        while(it != idx.end() && count < 10) {
            if(ckmax(current, mp(ll(S[*it] - '0') - ll(count + 1LL), -(*it)))) {
                could = true;
            }
            count++;
            it++;
        }
        //? dbg(i, could, ans);
        if(!could) {
            ans.pb(S[i]);
            i++;
        } else {
            auto [d, tar_idx] = current;
            ans.pb(ts(d).ft);
            safeErase(idx, -tar_idx);
        }
    }
    return ans;
}

str slv2(str s) {
    vpl arr;
    for(int i =0 ; i<s.size(); i++) {
        arr.push_back({s[i]-'0', i});
    }
    for(int i = 0; i<s.size(); i++) {
 
        ll cnt = 0;
        str ops = s.substr(i+1, 9);
        ll curr = s[i]-'0';
        ll lim = 0;
        for(int k = 0; k<ops.size(); k++){
            if(((ops[k]-'0')-(k+1))>curr) {
                curr = ((ops[k]-'0')-(k+1));
                lim = k+1;
            }
        }
 
        for(int k = lim+i-1; k>=i; k--) {
            s[k+1] = s[k];
        }
        str aux = to_string(curr);
        s[i] = aux[0];
    }
    return s;
}

str slv3(str s) {
    stringstream st(s);
    list<int>l;
    char ci;
    while (st >> ci) l.push_back((int)( ci-'0' ));
    vi ans;
    while (not l.empty()) {
      auto d = l.begin();
      auto d2=l.begin();
      int idx =0;
      int max = 0;
      while (d != l.end()) {
        if (9 - idx <= max) break;
        int v = *d - idx;
        if (v > max) 
        {
          max = v;
          d2=d;
        }
        idx++;
        d++;
      }
      d--;
      l.erase(d2);
      ans.push_back(max);
    }
    str response;
    each(x, ans) response.pb(ts(x).ft);
    return response;
}

void solve() {
    //? <>
    str S; cin >> S;
    //? dbg(S);
    str ans = slv(S);
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(1) {
        RAYA;
        int N = rng_int(int(2e5), int(2e5));
        str S; rep(N) S.pb(char('0' + rng_int(0, 9)));
        dbg(N);
        db last = time_elapsed();
        str ans = slv3(S);
        db current = time_elapsed();
        db taken = current - last;
        dbg(taken);
        if(taken > db(2)) {
            chk(false);
        }
    }

    int t = 1; cin >> t;
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
