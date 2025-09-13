//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

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
//* /Template

vi brute(int n, V<vi> a) {
    vi res{INF, INF, INF};

    int sizeMx = 0;
    for(auto& vec: a) sizeMx = max(sizeMx, sz(vec));

    sor(a);
    do {
        vi cur;
        for(int i = 0; i < sizeMx; i++) {
            for(int j = n - 1; j >= 0; j--) {
                if(i < sz(a[j])) {
                    cur.emplace_back(a[j][i]);
                    break;
                }
            }
        }
        ckmin(res, cur);
    } while(next_permutation(all(a)));
    return res;
}

vi slv(int n, V<vi> a) {
    for(auto& vec: a) reverse(all(vec));

    vector<int> response;
    vector<int> active;
    for(int i = 0; i < n; i++) active.emplace_back(i);
    while(!active.empty()) {
        RAYA;
        dbg("ga");
        dbg(a);
        dbg(active);
        vector<int> cands;
        for(int i = 0; i < sz(active); i++) {
            cands.emplace_back(active[i]);
        }

        vector<int> candsGuarda = cands;
        // dbg(cands);
        // cands apunte a un active

        vector<int> bucket;
        auto rem = [&](int id) -> void {
            int size = sz(a[id]);
            dbg("erasing", id, size);

            for(auto& x: a[id]) bucket.emplace_back(x);
            vector<int> newActive;

            for(auto& x: candsGuarda) {
                for(int i = 0; i < size; i++) {
                    if(a[x].empty()) break;
                    a[x].pop_back();
                }
                if(a[x].empty()) {

                } else {
                    newActive.emplace_back(x);
                }
            }
            active = newActive;
        };


        int offset = 0;
        while(true) {
            dbg("looking", cands);
            int idToBeErased = -1;
            for(int i = 0; i < sz(cands); i++) {
                int nxt = (a[cands[i]].size() - 1) - offset;

                if(nxt < 0) {
                    idToBeErased = i;
                    break;
                }
            }

            if(idToBeErased != -1) {
                dbg("end of some array", idToBeErased);
                // finish
                // normalize
                rem(cands[idToBeErased]);
                break;
            } else {
                dbg("finding mn");
                int mn = INF;
                for(int i = 0; i < sz(cands); i++) {
                    int nxt_id = (a[cands[i]].size() - 1) - offset;

                    mn = min(mn, a[cands[i]][nxt_id]);
                }

                vector<int> newCands;
                for(int i = 0; i < sz(cands); i++) {
                    int nxt_id = (a[cands[i]].size() - 1) - offset;

                    if(mn == a[cands[i]][nxt_id]) {
                        newCands.emplace_back(cands[i]);
                    }
                }

                if(sz(newCands) == 1) {
                    dbg("unique mn", mn, newCands.front());
                    // finish
                    idToBeErased = newCands.front();
                    rem(newCands.front());
                    // normalize
                    break;
                } else {
                    cands = newCands;
                    offset++;
                }
            }
        }

        reverse(all(bucket));
        for(auto& x: bucket) response.emplace_back(x);
    }
    return response;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> a;
    for(int i = 0; i < n; i++) {
        int k; cin >> k;
        vector<int> temp(k);
        for(auto& x: temp) cin >> x;
        a.emplace_back(temp);
    }
    dbg(n);
    for(auto& vec: a) dbg(vec);



    vi response = slv(n, a);

    for(auto& x: response) cout << x << " ";
    cout << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(0) {
        RAYA;
        RAYA;
        RAYA;
        int n = rng_ll(1, 5);
        V<vi> a;
        for(int i = 0; i < n; i++) {
            int k = rng_ll(1, 5);
            vi temp(k);
            for(auto& x: temp) x = rng_ll(1, 5);
            a.emplace_back(temp);
        }

        dbg(n);
        for(auto& vec: a) dbg(vec);

        vi ans = brute(n, a);
        dbg("Greedy");
        dbg("Greedy");
        dbg("Greedy");
        vi gre = slv(n, a);
        dbg("/Greedy");
        dbg("/Greedy");
        dbg("/Greedy");
        dbg("/Greedy");
        dbg(ans);
        dbg(gre);
        assert(ans == gre);
    }

    int t = 1;
    cin >> t;
    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        solve();
    }


    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
