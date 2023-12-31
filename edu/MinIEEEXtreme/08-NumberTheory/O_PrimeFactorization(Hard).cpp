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

struct Mint {
  uint64_t n;
  static uint64_t mod, inv, r2;
  Mint() : n(0) { }
  Mint(const uint64_t &x) : n(init(x)) { }
  static uint64_t init(const uint64_t &w) { return reduce(__uint128_t(w) * r2); }
  static void set_mod(const uint64_t &m) {
    mod = inv = m;
    for(int i = 0; i < 5; i++)  inv *= 2 - inv * m;
    r2 = -__uint128_t(m) % m;
  }
  static uint64_t reduce(const __uint128_t &x) {
    uint64_t y = uint64_t(x >> 64) - uint64_t((__uint128_t(uint64_t(x) * inv) * mod) >> 64);
    return int64_t(y) < 0 ? y + mod : y;
  }
  Mint& operator+= (const Mint &x) { n += x.n - mod; if(int64_t(n) < 0) n += mod; return *this; }
  Mint& operator+ (const Mint &x) const { return Mint(*this) += x; }
  Mint& operator*= (const Mint &x) { n = reduce(__uint128_t(n) * x.n); return *this; }
  Mint& operator* (const Mint &x) const { return Mint(*this) *= x; }
  uint64_t val() const { return reduce(n); }
};

uint64_t Mint::mod, Mint::inv, Mint::r2;

bool suspect(const uint64_t &a, const uint64_t &s, uint64_t d, const uint64_t &n) {
  if(Mint::mod != n)  Mint::set_mod(n);
  Mint x(1), xx(a), one(x), minusone(n - 1);
  while(d > 0) {
    if(d & 1) x *= xx;
    xx *= xx;
    d >>= 1;
  }
  if(x.n == one.n)  return true;
  for(unsigned int r = 0; r < s; r++) {
    if(x.n == minusone.n) return true;
    x *= x;
  }
  return false;
}

bool is_prime(const uint64_t &n) {
  if(n <= 1 || (n > 2 && (~n & 1))) return false;
  uint64_t d = n - 1, s = 0;
  while(~d & 1) s++, d >>= 1;
  static const uint64_t a_big[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  static const uint64_t a_smol[] = {2, 7, 61};
  if(n <= 4759123141LL) {
    for(auto &&p : a_smol) {
      if(p >= n)  break;
      if(!suspect(p, s, d, n))  return false;
    }
  } else {
    for(auto &&p : a_big) {
      if(p >= n)  break;
      if(!suspect(p, s, d, n))  return false;
    }
  }
  return true;
}

uint64_t rho_pollard(const uint64_t &n) {
  if(~n & 1)  return 2u;
  static random_device rng;
  uniform_int_distribution<uint64_t> rr(1, n - 1);
  if(Mint::mod != n)  Mint::set_mod(n);
  for(;;) {
    uint64_t c_ = rr(rng), g = 1, r = 1, m = 500;
    Mint y(rr(rng)), xx(0), c(c_), ys(0), q(1);
    while(g == 1) {
      xx.n = y.n;
      for(unsigned int i = 1; i <= r; i++)  y *= y, y += c;
      uint64_t k = 0; g = 1;
      while(k < r && g == 1) {
        for(unsigned int i = 1; i <= (m > (r - k) ? (r - k) : m); i++) {
          ys.n = y.n;
          y *= y; y += c;
          uint64_t xxx = xx.val(), yyy = y.val();
          q *= Mint(xxx > yyy ? xxx - yyy : yyy - xxx);
        }
        g = __gcd<uint64_t>(q.val(), n);
        k += m;
      }
      r *= 2;
    }
    if(g == n)  g = 1;
    while(g == 1) {
      ys *= ys; ys += c;
      uint64_t xxx = xx.val(), yyy = ys.val();
      g = __gcd<uint64_t>(xxx > yyy ? xxx - yyy : yyy - xxx, n);
    }
    if(g != n && is_prime(g)) return g;
  }
  assert(69 == 420);
}

template <typename T>
vector<T> factor(T n) {
  if(n < 2) return { };
  if(is_prime(n)) return {n};
  T d = rho_pollard(static_cast<uint64_t>(n));
  vector<T> l = factor(d), r = factor(n / d);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}

void solve() {
    uint64_t n;
    cin >> n;

    vector<uint64_t> fac = factor(n);
    sor(fac);

    cout << sz(fac) << " ";
    for(auto &&f : fac) {
        cout << f << " ";
    }
    cout << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll Q = 1LL;
    cin >> Q;

    while(Q--)
        solve();

    return 0;
}
