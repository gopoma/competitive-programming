//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

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

void solve() {
    int n; cin >> n;
    using vs = V<str>;
    vs a(n); for(auto& x: a) cin >> x;
    dbg(n);
    dbg(a);

    str color = "RGBYW";
    vi  value{1, 2, 3, 4, 5};

    int res = int(1e9);
    for(int mask = 0; mask < (1 << 10); mask++) {
        map<char, bool> colorThere;
        map<int, bool>  valueThere;
        for(int bit = 0; bit < 5; bit++) {
            colorThere[color[bit]] = bool(mask & (1 << bit));
            valueThere[value[bit]] = bool(mask & (1 << (5 + bit)));
        }

        bool ok = true;
        for(int i = 0; i < n && ok; i++) {
            char C = a[i][0];
            int  V = int(a[i][1] - '0');

            bool cT = colorThere[C];
            bool vT = valueThere[V];
            if(cT && vT) {

            } else if(cT && !vT) {
                for(int j = 0; j < n; j++) {
                    if(i == j) continue;

                    char C2 = a[j][0];
                    int  V2 = int(a[j][1] - '0');
                    bool cT2 = colorThere[C2];
                    bool vT2 = valueThere[V2];

                    if(cT2 && vT2) {
                        continue;
                    }

                    if(C == C2 && V != V2) {
                        ok = false;
                        break;
                    }
                }
            } else if(!cT && vT) {
                for(int j = 0; j < n; j++) {
                    if(i == j) continue;

                    char C2 = a[j][0];
                    int  V2 = int(a[j][1] - '0');
                    bool cT2 = colorThere[C2];
                    bool vT2 = valueThere[V2];

                    if(cT2 && vT2) {
                        continue;
                    }

                    if(C != C2 && V == V2) {
                        ok = false;
                        break;
                    }
                }
            } else {
                for(int j = 0; j < n; j++) {
                    if(i == j) continue;

                    char C2 = a[j][0];
                    int  V2 = int(a[j][1] - '0');
                    bool cT2 = colorThere[C2];
                    bool vT2 = valueThere[V2];

                    if(!cT2 && !vT2 && (make_pair(C, V) != make_pair(C2, V2))) {
                        ok = false;
                        break;
                    }
                }
            }

        }

        if(ok) {
            res = min(res, __builtin_popcount(mask));
        }
    }

    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();
}
