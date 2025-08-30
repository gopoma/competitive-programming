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

string to_string(vector<bool> v) {
    bool first = true;
    string res = "[";
    for (auto x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += x ? "true" : "false";
    }
    res += "]";
    return res;
}

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

const bool isDebugging = true;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA

const bool isDebugging = false;
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
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}


//* Template
ll rng_ll(ll L, ll R) { assert(L <= R);
    return uniform_int_distribution<ll>(L,R)(rng);  }
//* /Template

ll MEX(vector<ll> a) {
    const int n = sz(a);
    set<ll> S;
    for(auto& x: a) S.emplace(x);
    ll mex = 0;
    while(S.count(mex)) mex++;
    return mex;
}

ll work(vector<vector<ll>> a) {
    const int n = sz(a);
    const int m = sz(a.front());

    ll re = 0;
    for(int xl = 0; xl < n; xl++) {
        for(int xr = xl; xr < n; xr++) {
            for(int yl = 0; yl < n; yl++) {
                for(int yr = yl; yr < n; yr++) {
                    vl temp;
                    for(int x = xl; x <= xr; x++) {
                        for(int y = yl; y <= yr; y++) {
                            temp.emplace_back(a[x][y]);
                        }
                    }
                    re += MEX(temp);
                }
            }
        }
    }

    return re;
}

void brute(ll n) {
    vl p(n * n); iota(all(p), 0);

    ll mx = -BIG;
    vector<vector<ll>> re;
    do {
        vector<vector<ll>> a(n, vector<ll>(n));
        int id = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                a[i][j] = p[id++];
            }
        }
        ll cnt = work(a);
        if(cnt > mx) {
            mx = cnt;
            re = a;
        }
    } while(next_permutation(all(p)));

    do {
        vector<vector<ll>> a(n, vector<ll>(n));
        int id = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                a[i][j] = p[id++];
            }
        }
        ll cnt = work(a);
        if(cnt == mx) {
            RAYA;
            for(auto& vec: a) dbg(vec);
        }
    } while(next_permutation(all(p)));
}

vector<vector<int>> formSpiralMatrix(vi arr, int R, int C) {
    vector<vector<int>> mat(R, vector<int>(C));

    int top = 0,
        bottom = R - 1,
        left = 0,
        right = C - 1;

    int index = 0;

    while (1) {

        if (left > right)
            break;

        // print top row
        for (int i = left; i <= right; i++)
            mat[top][i] = arr[index++];
        top++;

        if (top > bottom)
            break;

        // print right column
        for (int i = top; i <= bottom; i++)
            mat[i][right] = arr[index++];
        right--;

        if (left > right)
            break;

        // print bottom row
        for (int i = right; i >= left; i--)
            mat[bottom][i] = arr[index++];
        bottom--;

        if (top > bottom)
            break;

        // print left column
        for (int i = bottom; i >= top; i--)
            mat[i][left] = arr[index++];
        left++;
    }

    return mat;
}

void solve() {
    ll n; cin >> n;
    vi a(n * n); iota(all(a), 0);
    vector<vector<int>> re = formSpiralMatrix(a, n, n);
    for(auto& vec: re) for(auto& x: vec) x = (n * n) - x;
    for(auto& vec: re) {
        for(auto& x: vec) {
            cout << (x - 1) << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;
    while(t--) {
        RAYA;
        solve();
    }

    return 0;
}
