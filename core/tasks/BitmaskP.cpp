//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;

//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return string(1, c);
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

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(xd) << "\033[0m" << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m";)

#define GA          dbg(0)
#define RAYA        cout << "\033[101m" << "================================" << "\033[0m" << endl;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
#endif
//* /Debugger

using ll = long long;
using db = long double; // or double if tight TL
using str = string;

using pi = pair<int,int>;
using pl = pair<ll, ll>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vl = V<ll>;
using vb = V<bool>;
using vpi = V<pi>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int dx[9]{0, -1, -1, -1,  0,  0, +1, +1, +1};
int dy[9]{0, -1,  0, +1, -1, +1, -1,  0, +1};

using Info = V<V<bool>>;
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
void solve() {
    int n, m; cin >> n >> m;
    Info start(n, V<bool>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c; cin >> c;
            start[i][j] = (c == '*');
        }
    }
    dbg(n, m);

    vpi E;
    for(int col = 0; col < m; col++) E.emplace_back(0, col);
    for(int row = 0; row < n; row++) E.emplace_back(row, 0);
    remDup(E);
    dbg(E);

    auto check = [&](int i, int j) -> bool {
        return ((0 <= i && i < n) && (0 <= j && j < m));
    };
    auto doOpt = [&](Info& G, int i, int j) -> void {
        for(int k = 0; k < 9; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if(check(ni, nj)) {
                G[ni][nj] = !G[ni][nj];
            }
        }
    };

    const Info target = V<V<bool>>(n, V<bool>(m, true));
    const ll BIG = ll(1e18);

    const int N = sz(E);
    ll res = BIG;
    for(int mask = 0; mask < (1 << N); mask++) {
        Info G = start;
        ll local_res = 0;
        for(int bit = 0; bit < N; bit++) {
            if(mask & (1LL << bit)) {
                auto [i, j] = E[bit];
                doOpt(G, i, j);
                local_res++;
            }
        }

        for(int row = 1; row < n; row++) {
            for(int col = 1; col < m; col++) {
                int ni = row - 1;
                int nj = col - 1;
                assert(check(ni, nj));
                if(!G[ni][nj]) {
                    doOpt(G, row, col);
                    local_res++;
                }
            }
        }

        if(G == target) {
            res = min(res, local_res);
        }
    }

    if(res >= BIG) cout << "-1\n";
    else cout << res << "\n";
}

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
