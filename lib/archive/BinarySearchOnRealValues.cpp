#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debugICPC.h"

#define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define chk(...)
#define RAYA
#endif

#define tcT template<class T

using ll = long long;
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
const long double PI = acos((long double)-1);
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

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

const double EPS = (double)(1e-9);

bool eq(double A, double B) {
    return A - B < EPS;
}

void solve() {
    str lxd, rxd; cin >> lxd >> rxd;
    double l = stod(lxd);
    double r = stod(rxd);
    //? dbg(l, r);

    auto F = [&](double x) -> double {
        return (l*cos(PI-x)+r) * (l*cos(PI-x)+r) * (l*sin(PI-x) + r*tan(PI-x)) - (r)*(r)*(r*tan(PI-x));
    };

    auto ff = [&](double x) -> double {
        return (l * (double(3)*l*l*cos(double(3)*x) - double(12)*l*r*cos(double(2)*x) + (double(12)*r*r+l*l)*cos(x))) / (double(4));
    };

    auto check = [&](double x) {
        return ff(x) < 0.0;
    };

    auto get = [&](double L, double R) -> double {
        // Bolzano's Theorem
        double l_real = L, r_real = R;
        long long l = reinterpret_cast<long long&>(l_real);
        long long r = reinterpret_cast<long long&>(r_real);
        for(int i = 0; i < 100; i++) {
            long long mid = l + (r - l) / 2;
            if (check(reinterpret_cast<double&>(mid)))
                r = mid;
            else
                l = mid + 1;
        }
        double ans = reinterpret_cast<double&>(l);
        return ans;
    };

    double gL = EPS;
    double gR = PI - EPS;

//?    double act = get(gL, gR);
//?    double MX = F(act);
//?    double ans = act;

double ans = get(PI / double(2) - 0.3, gR);

//?    auto upd = [&](double L, double R) -> void {
//?        double act = get(L, R);
//?        if(ckmax(MX, F(act))) {
//?            ans = act;
//?        }
//?    };
//?    upd(PI / double(2), gR);

    //? dbg(ans);
    cout << ans << "\n";
}

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

int main() {
    //? setIn("M.in");
    cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams

    cout << fixed << setprecision(12);
    cerr << fixed << setprecision(12);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) {
        solve();
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif

    return 0;
}
