//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

// building blocks
using ll  = long long;
using db  = long double; // or double, if TL is tight
using str = string;      // yay python!

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
//! ^ lol this makes everything look weird but I'll try it

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
tcT > int lwb(V<T> &a, const T &b) { return int(lb(all(a), b) - bg(a)); }
tcT > int upb(V<T> &a, const T &b) { return int(ub(all(a), b) - bg(a)); }



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); }  // # of bits set
constexpr int bits(int x) {  // assert(x >= 0); // make C++11 compatible until
	                         // USACO updates ...
	return x == 0 ? 0 : 31 - __builtin_clz(x);
}  // floor(log2(x))
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }

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

tcTU > T fstTrue(T lo, T hi, U f) {
	++hi;
	assert(lo <= hi);  // assuming f is increasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo) / 2;
		f(mid) ? hi = mid : lo = mid + 1;
	}
	return lo;
}
tcTU > T lstTrue(T lo, T hi, U f) {
	--lo;
	assert(lo <= hi);  // assuming f is decreasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo + 1) / 2;
		f(mid) ? lo = mid : hi = mid - 1;
	}
	return lo;
}
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



#define tcTUU tcT, class ...U

inline namespace IO {
#define SFINAE(x, ...)                                                         \
	template <class, class = void> struct x : std::false_type {};              \
	template <class T> struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

template <auto &is> struct Reader {
	template <class T> void Impl(T &t) {
		if constexpr (DefaultI<T>::value) is >> t;
		else if constexpr (Iterable<T>::value) {
			for (auto &x : t) Impl(x);
		} else if constexpr (IsTuple<T>::value) {
			std::apply([this](auto &...args) { (Impl(args), ...); }, t);
		} else static_assert(IsTuple<T>::value, "No matching type for read");
	}
	template <class... Ts> void read(Ts &...ts) { ((Impl(ts)), ...); }
};

template <class... Ts> void re(Ts &...ts) { Reader<cin>{}.read(ts...); }
#define def(t, args...)                                                        \
	t args;                                                                    \
	re(args);

template <auto &os, bool debug, bool print_nd> struct Writer {
	string comma() const { return debug ? "," : ""; }
	template <class T> constexpr char Space(const T &) const {
		return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n'
		                                                             : ' ';
	}
	template <class T> void Impl(T const &t) const {
		if constexpr (DefaultO<T>::value) os << t;
		else if constexpr (Iterable<T>::value) {
			if (debug) os << '{';
			int i = 0;
			for (auto &&x : t)
				((i++) ? (os << comma() << Space(x), Impl(x)) : Impl(x));
			if (debug) os << '}';
		} else if constexpr (IsTuple<T>::value) {
			if (debug) os << '(';
			std::apply(
			    [this](auto const &...args) {
				    int i = 0;
				    (((i++) ? (os << comma() << " ", Impl(args)) : Impl(args)),
				     ...);
			    },
			    t);
			if (debug) os << ')';
		} else static_assert(IsTuple<T>::value, "No matching type for print");
	}
	template <class T> void ImplWrapper(T const &t) const {
		if (debug) os << "\033[0;31m";
		Impl(t);
		if (debug) os << "\033[0m";
	}
	template <class... Ts> void print(Ts const &...ts) const {
		((Impl(ts)), ...);
	}
	template <class F, class... Ts>
	void print_with_sep(const std::string &sep, F const &f,
	                    Ts const &...ts) const {
		ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
	}
	void print_with_sep(const std::string &) const { os << '\n'; }
};

template <class... Ts> void pr(Ts const &...ts) {
	Writer<cout, false, true>{}.print(ts...);
}
template <class... Ts> void ps(Ts const &...ts) {
	Writer<cout, false, true>{}.print_with_sep(" ", ts...);
}
}  // namespace IO

inline namespace Debug {

#ifdef LOCAL
#include "helpers/debug.h"

#define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define chk(...)
#define RAYA
#endif

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}
}  // namespace Debug



inline namespace FileIO {
void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void setIO(str s = "") {
	cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
	//? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);
	cin.exceptions(cin.failbit);
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) setIn(s + ".in"), setOut(s + ".out");  // for old USACO
}
}  // namespace FileIO



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

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

//? /Custom Helpers



//* Template
/**
 * Description: Big Integer
 * Source: https://github.com/indy256/codelibrary/blob/master/cpp/numeric/bigint.cpp
	* oops that one uses FFT instead of Karatsuba now ....
 * Verification: https://oj.uz/problem/view/IOI11_parrots
 */

// base and base_digits must be consistent
const int base = 1e9, base_digits = 9;
struct bigint { // value == 0 is represented by empty z
	vi z; // digits
	int sign; // sign == 1 <==> value >= 0
	bigint() : sign(1) {} // sign == -1 <==> value < 0
	bigint(ll v) { *this = v; }
	bigint &operator=(ll v) {
		sign = v < 0 ? -1 : 1; v *= sign; // make v positive
		z.clear(); for (;v;v/=base) z.pb(v%base);
		return *this;
	}
	bigint(const str &s) { read(s); } // add char by char

	bigint &operator+=(const bigint &other) {
		//dbg("ADDING",*this,other,sign,other.sign);
		if (sign == other.sign) {
			for (int i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
				if (i == sz(z)) z.pb(0);
				z[i] += carry+(i<sz(other.z)?other.z[i]:0);
				carry = z[i] >= base; if (carry) z[i] -= base;
			}
		} else if (other != 0 /* prevent infinite loop */) *this -= -other;
		return *this;
	}
	friend bigint operator+(bigint a, const bigint &b) { return a += b; }
	bigint &operator-=(const bigint &other) {
		if (sign == other.sign) {
			if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
				for (int i = 0, carry = 0; i < sz(other.z) || carry; ++i) {
					z[i] -= carry+(i<sz(other.z)?other.z[i]:0);
					carry = z[i]<0; if (carry) z[i] += base;
				}
				trim();
			} else { // result will change sign
				*this = other-*this;
				this->sign = -this->sign;
			}
		} else *this += -other;
		return *this;
	}
	friend bigint operator-(bigint a, const bigint &b) { return a -= b; }

	bigint &operator*=(int v) { // oops make sure not to multiply by ll ...
		if (v < 0) sign = -sign, v = -v;
		for (int i = 0, carry = 0; i < sz(z) || carry; ++i) {
			if (i == sz(z)) z.pb(0);
			ll cur = (ll)z[i]*v+carry;
			carry = cur/base; z[i] = cur%base;
		}
		trim(); return *this;
	}
	bigint operator*(int v) const { return bigint(*this) *= v; }
	friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
		int norm = base/(b1.z.bk+1);
		bigint a = a1.abs()*norm, b = b1.abs()*norm, q, r; // make last element of b big
		q.z.rsz(sz(a.z));
		R0F(i,sz(a.z)) {
			r *= base; r += a.z[i];
			int s1 = sz(b.z) < sz(r.z) ? r.z[sz(b.z)] : 0;
			int s2 = sz(b.z)-1 < sz(r.z) ? r.z[sz(b.z)-1] : 0;
			int d = ((ll)s1*base+s2)/b.z.bk; // best approximation
			r -= b*d; while (r < 0) r += b, --d;
			q.z[i] = d;
		}
		q.sign = a1.sign*b1.sign; r.sign = a1.sign;
		q.trim(); r.trim(); return {q,r/norm};
	}
	friend bigint sqrt(const bigint &a1) {
		bigint a = a1; while (!sz(a.z) || sz(a.z)&1) a.z.pb(0);
		int n = sz(a.z), firstDigit = ::sqrt((db)a.z[n-1]*base+a.z[n-2]);
		int norm = base/(firstDigit+1); a *= norm; a *= norm;
		while (!sz(a.z) || sz(a.z)&1) a.z.pb(0);
		bigint r = (ll)a.z[n-1]*base+a.z[n-2];
		firstDigit = (int)::sqrt((db)a.z[n-1]*base+a.z[n-2]);
		int q = firstDigit; bigint res;
		R0F(j,n/2) {
			for (;; --q) {
				bigint r1 = (r-(res*2*base+q)*q)*base*base +
							(j>0?(ll)a.z[2*j-1]*base+a.z[2*j-2]:0);
				if (r1 >= 0) { r = r1; break; }
			}
			res *= base; res += q; // add a bit to sqrt
			if (j > 0) {
				int d1 = sz(res.z)+2 < sz(r.z) ? r.z[sz(res.z)+2] : 0; // always 0/1?
				int d2 = sz(res.z)+1 < sz(r.z) ? r.z[sz(res.z)+1] : 0;
				int d3 = sz(res.z) < sz(r.z) ? r.z[sz(res.z)] : 0;
				q = ((ll) d1*base*base+(ll)d2*base+d3)/(firstDigit*2);
			}
		}
		res.trim(); return res/norm;
	}
	bigint operator/(const bigint &v) const { return divmod(*this, v).f; }
	bigint operator%(const bigint &v) const { return divmod(*this, v).s; }
	bigint &operator/=(int v) {
		if (v < 0) sign = -sign, v = -v;
		for (int i = sz(z)-1, rem = 0; i >= 0; --i) {
			ll cur = z[i]+rem*(ll)base;
			z[i] = cur/v; rem = cur%v;
		}
		trim(); return *this;
	}
	bigint operator/(int v) const { return bigint(*this) /= v; }
	int operator%(int v) const {
		if (v < 0) v = -v;
		int m = 0; R0F(i,sz(z)) m = (z[i]+m*(ll)base)%v;
		return m*sign; }
	bigint &operator*=(const bigint &v) { return *this = *this*v; }
	bigint &operator/=(const bigint &v) { return *this = *this/v; }

	bool operator<(const bigint &v) const {
		if (sign != v.sign) return sign < v.sign;
		if (sz(z) != sz(v.z)) return sz(z)*sign < sz(v.z) * v.sign;
		R0F(i,sz(z)) if (z[i] != v.z[i]) return z[i]*sign < v.z[i]*sign;
		return 0; // equal
	}
	bool operator>(const bigint &v) const { return v < *this; }
	bool operator<=(const bigint &v) const { return !(v < *this); }
	bool operator>=(const bigint &v) const { return !(*this < v); }
	bool operator==(const bigint &v) const { return !(*this < v) && !(v < *this); }
	bool operator!=(const bigint &v) const { return *this < v || v < *this; }
	void trim() {
		while (sz(z) && z.bk == 0) z.pop_back();
		if (!sz(z)) sign = 1; // don't output -0
	}
	bool isZero() const { return !sz(z); }
	friend bigint operator-(bigint v) {
		if (sz(v.z)) v.sign = -v.sign;
		return v; }
	bigint abs() const { return sign == 1 ? *this : -*this; }
	ll longValue() const {
		ll res = 0; R0F(i,sz(z)) res = res*base+z[i];
		return res*sign; }
	friend bigint gcd(const bigint &a, const bigint &b) {
		return b.isZero() ? a : gcd(b, a % b); } // euclidean algo
	friend bigint lcm(const bigint &a, const bigint &b) {
		return a/gcd(a, b) * b; }

	void read(const str &s) {
		sign = 1; z.clear(); int pos = 0;
		while (pos < sz(s) && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-') sign = -sign;
			++pos; } // account for sign
		for (int i = sz(s)-1; i >= pos; i -= base_digits) {
			int x = 0;
			for (int j = max(pos, i-base_digits+1); j <= i; j++)
				x = x*10+s[j]-'0';
			z.pb(x);
		}
		trim();
	}
	friend istream &operator>>(istream &is, bigint &v) {
		str s; is >> s; v.read(s); return is; }
	friend ostream &operator<<(ostream &os, const bigint &v) {
		if (v.sign == -1) os << '-';
		os << (!sz(v.z) ? 0 : v.z.bk);
		R0F(i,sz(v.z)-1) os << setw(base_digits) << setfill('0') << v.z[i];
		return os; // pad with zeroes
	}
	static vi convert_base(const vi &a, int old_digits, int new_digits) {
		vl p(max(old_digits, new_digits) + 1); // blocks of 10^{old} -> 10^{new}
		p[0] = 1; FOR(i,1,sz(p)) p[i] = p[i-1]*10;
		vi res; ll cur = 0; int cur_digits = 0;
		for (int v:a) {
			cur += v*p[cur_digits]; cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.pb(cur%p[new_digits]);
				cur /= p[new_digits]; cur_digits -= new_digits;
			}
		}
		res.pb(cur); while (sz(res) && res.bk == 0) res.pop_back();
		return res;
	}
	static vl karatMul(const vl &a, const vl &b) { // karatsuba
		int n = sz(a); vl res(2*n);
		if (n <= 32) { // naive multiply
			F0R(i,n) F0R(j,n) res[i+j] += a[i]*b[j];
			return res; }
		int k = n/2;
		vl a1(begin(a),begin(a)+k), a2(k+all(a));
		vl b1(begin(b),begin(b)+k), b2(k+all(b));
		vl a1b1 = karatMul(a1, b1), a2b2 = karatMul(a2, b2);
		F0R(i,k) a2[i] += a1[i], b2[i] += b1[i];
		vl r = karatMul(a2, b2); // three instead of four products
		F0R(i,sz(a1b1)) r[i] -= a1b1[i];
		F0R(i,sz(a2b2)) r[i] -= a2b2[i];
		F0R(i,sz(r)) res[i+k] += r[i];
		F0R(i,sz(a1b1)) res[i] += a1b1[i];
		F0R(i,sz(a2b2)) res[i+n] += a2b2[i];
		return res;
	}
	bigint operator*(const bigint &v) const {
		if (min(sz(z),sz(v.z)) < 150) return mul_simple(v);
		bigint res; res.sign = sign*v.sign; // should work as long as # of digits isn't too large (> LLONG_MAX/10^{12})
		vi a6 = convert_base(this->z, base_digits, 6); // blocks of 10^6 instead of 10^9
		vi b6 = convert_base(v.z, base_digits, 6);
		vl a(all(a6)), b(all(b6));
		while (sz(a) < sz(b)) a.pb(0);
		while (sz(b) < sz(a)) b.pb(0);
		while (sz(a)&(sz(a)-1)) a.pb(0), b.pb(0); // make size power of 2
		vl c = karatMul(a, b);
		ll cur = 0; F0R(i,sz(c)) { // process carries
			cur += c[i]; res.z.pb(cur%1000000); cur /= 1000000; }
		res.z = convert_base(res.z,6,base_digits);
		res.trim(); return res;
	}
	bigint mul_simple(const bigint &v) const {
		bigint res; res.sign = sign*v.sign;
		res.z.rsz(sz(z)+sz(v.z));
		F0R(i,sz(z)) if (z[i]) {
			ll cur = 0; for (int j = 0; j < sz(v.z) || cur; ++j) {
				cur += res.z[i+j]+(ll)z[i]*(j<sz(v.z)?v.z[j]:0);
				res.z[i+j] = cur%base; cur /= base;
			}
		}
		res.trim(); return res;
	}
	friend str ts(const bigint& v) {
		stringstream ss; ss << v;
		str s; ss >> s; return s; }
};

bigint random_bigint(int n) {
	str s; F0R(i,n) s += rand() % 10 + '0';
	return bigint(s); }

// random tests
void bigintTest() {
	bigint x = bigint("120");
	bigint y = bigint("5");
	cout << x / y << endl;
	F0R(i,1000) {
		int n = rand() % 100 + 1;
		bigint a = random_bigint(n), res = sqrt(a);
		bigint xx = res * res, yy = (res + 1) * (res + 1);
		if (xx > a || yy <= a) {
			dbg("SQRT FAILED",i);
			dbg(a,res);
			break;
		}
		int m = rand() % n + 1;
		bigint b = random_bigint(m)+1;
		res = a/b; xx = res*b, yy = b*(res+1);
		if (xx > a || yy <= a) {
			dbg("DIVISION FAILED",i);
			dbg(a,b,res);
			break;
		}
	}
	{
		bigint a = random_bigint(10000);
		bigint b = random_bigint(2000);
		auto t1 = chrono::high_resolution_clock::now();
		bigint c = a / b;
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> duration = t2 - t1;
		dbg(duration.count(),"ms");
	}
	bigint a = random_bigint(500000);
	bigint b = random_bigint(500000);
	bigint c1, c2;
	{
		auto t1 = chrono::high_resolution_clock::now();
		c1 = a * b;
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> duration = t2 - t1;
		dbg(duration.count(),"ms");
	}
	{
		auto t1 = chrono::high_resolution_clock::now();
		c2 = a.mul_simple(b);
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> duration = t2 - t1;
		dbg(duration.count(),"ms");
	}
	dbg(c1 == c2);
	{

		auto t1 = chrono::high_resolution_clock::now();
		F0R(i,1000000) {
			a = random_bigint(30);
			b = random_bigint(30);
			c2 = a.mul_simple(b);
		}
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> duration = t2 - t1;
		dbg(duration.count(),"ms");
	}
}

//* /Template

str brute(str S) {
    auto isPalindrome = [&](str w) -> bool {
        for(int i = 0; i < sz(w)/2; i++) if(w[i] != w[sz(w) - i - 1]) return false;
        return true;
    };
    bigint act = S;
    while(!isPalindrome(ts(act))) act += 1LL;
    return ts(act);
}

str slv(str S) {
    const int n = sz(S);
    str ans = S;
    auto updmn = [&](int i) {
        ans[i] = ans[n - i - 1] = min(S[i], S[n - i - 1]);
    };
    auto updmx = [&](int i) {
        ans[i] = ans[n - i - 1] = max(S[i], S[n - i - 1]);
    };

    for(int i = 0; i < n/2; i++) updmx(i);
    deque<pair<char, int>> xd;
    for(int i = 0; i < n/2; i++) {
        char L = S[i];
        char R = S[n - i - 1];
        if(L > R) xd.eb('>', i);
        else if(L < R) xd.eb('<', i);
    }
    while(!xd.empty() && xd.ft.f == '>') xd.pop_front();

    if(xd.empty()) return ans;
    else {
        const int m = sz(xd);
        for(int i = 0; i < m - 1; i++) {
            if(xd[i].f == '>') {
                updmx(xd[i].s);
            } else {
                updmn(xd[i].s);
            }
        }
        if(xd.bk.f == '<') {
            dbg('<');
            bool canAdd = false;
            for(int i = xd.bk.s + 1; i < n/2; i++) {
                canAdd |= (S[i] < '9');
            }
            if(n & 1) canAdd |= (S[n/2] < '9');

            if(canAdd) {
                dbg("Can Add");
                updmn(xd.bk.s);
                if((n & 1) && (S[n/2] != '9')) {
                    ans[n/2]++;
                    return ans;
                }
                for(int i = n/2 - 1; i > xd.bk.s; i--) {
                    if(S[i] != '9') {
                        ans[i] = ans[n - i - 1] = char(ans[i] + 1);
                        for(int j = i + 1; j < n/2; j++) {
                            ans[j] = ans[n - j - 1] = '0';
                        }
                        if(n & 1) ans[n/2] = '0';
                        return ans;
                    }
                }
            } else {
                dbg("Cannot Add");
                char L = S[xd.bk.s];
                char R = S[n - xd.bk.s - 1];
                ans[xd.bk.s] = ans[n - xd.bk.s - 1] = min(char(L + 1), max(L, R));

                if(ans[xd.bk.s] == char(L + 1) && (n & 1)) ans[n/2] = '0';
                if(ans[xd.bk.s] == char(L + 1))
                    for(int i = xd.bk.s + 1; i < n/2; i++)
                        ans[i] = ans[n - i - 1] = '0';
                return ans;
            }
        } else {
            dbg('>');
            chk(xd.bk.f == '>');
        }
        return ans;
    }
}
const bool go = false;

void solve() {
    def(str, S);

    str ans = slv(S);
    dbg(ans);
    ps(ans);
}


//? Generator
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator


signed main() {
    setIO();

    while(go) {
        RAYA;
        int n = rng_int(1, 7);
        str S; S.pb(ts(rng_int(1, 9)).ft);
        for(int i = 1; i < n; i++) S.pb(ts(rng_int(0, 9)).ft);
        dbg(n);
        dbg(S);
        str ans = brute(S);
        str greedy = slv(S);
        dbg(ans);
        dbg(greedy);
        chk(ans == greedy);
    }

    ll t = 1; //? re(t);

    FOR(i, 1, t + 1) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
