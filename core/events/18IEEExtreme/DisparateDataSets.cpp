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



//? Template
const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



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
//? /Template

void solve() {
    // TODO: ok
    vs lines;
    {
        str line;
        while(getline(cin, line)) {
            lines.eb(line);
        }
        each(x, lines) dbg(x);
    }



    // TODO: ok
    auto split = [&](str& S) -> vs {
        str current;
        deque<str> tokens;
        each(c, S) {
            if(c == ',') {
                tokens.eb(current);
                current.clear();
            } else {
                current.pb(c);
            }
        }
        tokens.eb(current);
        assert(sz(tokens) >= 6);

        deque<str> left;
        left.eb(tokens.ft); tokens.pop_front();
        deque<str> right;
        rep(4) {
            right.emplace_front(tokens.bk);
            tokens.pop_back();
        }
        vs ans;
        str middle;
        for(int i = 0; i < sz(tokens); i++) {
            if(i == sz(tokens) - 1) {
                middle += tokens[i];
            } else {
                middle += tokens[i];
                middle += ",";
            }
        }
        each(x, left) ans.eb(x);
        ans.eb(middle);
        each(x, right) ans.eb(x);

        return ans; 
    };



    // TODO: ok
    V<vs> info;
    each(line, lines) info.eb(split(line));



    RAYA;
    each(x, info) {
        dbg(x, sz(x));
        assert(sz(x) == 6);
    }

    //? 0 - Event ID,
    //? 1 - "Event Title"
    //? 2 - "Acronym"
    //? 3 - Project Code
    //? 4 - 3 Digit Project Code
    //? 5 - "Record Type"
    const str PARENT = "\"Parent Event\"";
    const str CHILD = "\"IEEE Event\"";
    map<str, pair<V<vs>, V<vs>>> database;
    //? first - parents
    //? second - children
    each(x, info) {
        str idEvent = x[0];
        str title = x[1];
        str acronym = x[2];
        str projectCode = x[3];
        str shortProjectCode = x[4];
        str type = x[5];

        if(type == PARENT) {
            database[acronym].first.emplace_back(x);
        } else {
            assert(type == CHILD);
            database[acronym].second.emplace_back(x);
        }
    }

    auto print = [&](vs x, bool has, str msg) -> void {
        assert(sz(x) == 6);
        str idEvent = x[0];
        str title = x[1];
        str acronym = x[2];
        str projectCode = x[3];
        str shortProjectCode = x[4];
        str type = x[5];
        cout << idEvent << "," << title << "," << acronym << "," << projectCode << "," << shortProjectCode << "," << type;
        if(has) cout << "," << msg;
        cout << "\n";
    };

    each(it, database) {
        auto [acro, it2] = it;
        if(acro == "") continue;

        auto [parent, children] = it2;
        dbg(acro, parent, children);

        if(sz(parent) != 1 || children.empty()) continue;

        set<str> uu;
        each(child, children) {
            str idEvent = child[0];
            str title = child[1];
            str acronym = child[2];
            str projectCode = child[3];
            str shortProjectCode = child[4];
            str type = child[5];

            uu.emplace(shortProjectCode);
        }
        if(sz(uu) == 1 && !(*uu.begin()).empty()) {
            parent.ft[4] = *uu.begin();
        } else {
            parent.ft[4] = "???";
        }

        print(parent.ft, false, "");
        sort(all(children), [&](vs& A, vs& B) {
            if(A[1] != B[1]) return A[1] < B[1];
            return A[0] < B[0];
        });

        each(child, children) print(child, true, parent.ft[0]);
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

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
