//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

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

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}



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
#define f first
#define s second



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



// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



const int MOD = 1e9+7;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
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
//? /Custom Helpers


void solve(int start_row, int start_col) {
    const int n = 8;
    auto isValid = [&](int row, int col) {
        return (0 <= row && row < n) && (0 <= col && col < n);
    };



    const vi ddx = {-2, -2, -1, +1, +2, +2, +1, -1};
    const vi ddy = {-1, +1, +2, +2, +1, -1, -2, -2};



    const int NONE = -79;
    AR<AR<int, n>, n> mtx; for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) mtx[i][j] = NONE;
    mtx[start_row][start_col] = 1;

    bool ok = false;
    #define check { if(ok) { return; } }

    auto get = [&](int row, int col, int parent_row, int parent_col) {
        assert(isValid(row, col));

        int R = 0;
        for(int k = 0; k < 8; k++) {
            int new_x = row + ddx[k];
            int new_y = col + ddy[k];

            if(isValid(new_x, new_y) && mtx[new_x][new_y] == NONE && !(new_x == parent_row && new_y == parent_col)) {
                R++;
            }
        }
        return R;
    };

    int cnt = 0;
    function<void(int, int, int)> backtrack = [&](int num, int row, int col) {
        cnt++;

        mtx[row][col] = num;

        if(num == n * n) {
            ok = true;
            check
        }

        check

        //? try
        vector<pair<int, pi>> go;
        for(int k = 0; k < 8; k++) {
            check

            int new_x = row + ddx[k];
            int new_y = col + ddy[k];

            if(isValid(new_x, new_y) && mtx[new_x][new_y] == NONE) {
                go.eb(mp(get(new_x, new_y, row, col), mp(new_x, new_y)));
            }

            check
        }

        sor(go);

        check

        if(go.empty()) {
            mtx[row][col] = NONE;
            return;
        }

        each(e, go) {
            check

            int act_row = e.s.f;
            int act_col = e.s.s;

            backtrack(num + 1, act_row, act_col);

            check
        }

        check

        mtx[row][col] = NONE;

        check
    }; backtrack(1, start_row, start_col);

    each(row, mtx) dbg(row);
    dbg(cnt);
    RAYA;

    each(row, mtx) {
        each(x, row)
            cout << x << " ";
        cout << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    //? cin >> t;

    for(int idx = 0; idx < t; idx++) {
        RAYA;
        RAYA;
        int start_row, start_col; cin >> start_row >> start_col; start_row--; start_col--; swap(start_row, start_col);
        dbg(start_row, start_col);

        solve(start_row, start_col);
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
