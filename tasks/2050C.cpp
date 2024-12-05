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

bool slv(str S) {
    ll sum = 0;
    map<ll, ll> hist;
    for(auto& c: S) {
        hist[ll(c - '0')]++;
        sum += ll(c - '0');
    }
    dbg(sum, hist);

    map<ll, ll> should;
    should[0] = 0;
    should[2] = 1;
    should[4] = 2;
    should[6] = 3;
    should[8] = 4;
    should[1] = 5;
    should[3] = 6;
    should[5] = 7;
    should[7] = 8;

    for(ll times = 0; times <= hist[3]; times++) {
        ll osum = sum + 6LL * times;
        ll need = 9LL - (osum % 9LL);
        //? dbg(times, osum, need, should[need], hist[2]);
        if(hist[2] >= should[need]) {
            return true;
        }
    }
    return false;
}

bool slv2(str s) {
    ll sum = 0;
    ll addSum = 0;
    vl arr(2, 0);
    for(int i = 0; i<s.size(); i++) {
        if(s[i]=='2') {
            arr[1]++;
            addSum+=2;
        }else if(s[i]=='3') {
            arr[0]++;
            addSum+=6;
        }
        sum+=(s[i]-'0');
    }
 
    if(sum%9==0) {
        return true;
        cout << "YES\n";
        //? return;
    }
 
    ll curr = cdiv(sum,9) * 9;
    // dbg(curr);
    bool flag = false;
    while(curr-sum <= addSum && (curr-sum)%2!=0) {
        curr+=9;
    }
    // dbg(curr, sum, addSum);
    // dbg(arr);
    if((curr-sum)%2==0 && curr-sum<=addSum) {
        ll gets = curr-sum;
        ll idx = 0;
        ll tot = 0;
        while(tot!=gets && idx!=2) {
            if(arr[idx]==0) {
                idx++;
                continue;
            }
            if(tot+(idx==0?6:2) > gets) {
                idx++;
                continue;
            }
            tot+=(idx==0?6:2);
            arr[idx]--;
        }
        if(tot==gets) {
            return true;
            cout << "YES\n";
        }else {
            return false;
            cout << "NO\n";
        }
    }else {
        return false;
        cout << "NO\n";
    }
}

bool slv3(str s) {
	ll n=s.size();
	ll sum=0,cant2=0,cant3=0;
	FOR(i,0,n){
		ll act=s[i]-'0';
		if(act==1 || act >=4 && act<=9){
			sum+=act;
		}
		else if(act==2){
			cant2++;
		}
		else if(act==3) cant3++;
	}
	dbg(sum);
	sum%=9;
	FOR(i,0,cant2+1){
		ll resto=2*i + 4*(cant2-i) + sum;
		if(resto%9==0){
            return true;
		}
		if(cant3>=1){
			if((resto+3)%9==0){
                return true;
			}
		}
		if(cant3>=2){
			if((resto+6)%9==0){
                return true;
			}
		}
	}
	return false;
}
 
void solve() {
    //? <>
    str S; cin >> S;
    bool ans = slv(S);
    cout << (ans?"YES":"NO") << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(1) {
        RAYA;
        int n = rng_int(1, int(1e5));
        str S; rep(n) S.pb(char('0'+rng_int(0, 9)));
        bool ans = slv(S);
        bool greedy = slv3(S);
        dbg(ans, greedy);
        chk(ans == greedy);
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
