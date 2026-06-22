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
//* /Template

void slv(int n, V<str> S) {
    str target = "win";

    vector<multiset<char>> E(n);
    map<char, map<char, vector<int>>> G;
    for(int i = 0; i < n; i++) {
        vector<char> extra;
        vector<char> need;

        map<char, int> hist;
        for(auto& c: S[i]) {
            hist[c]++;
            E[i].emplace(c);
        }

        for(auto& c: target) {
            if(hist[c] == 0) {
                need.emplace_back(c);
            }
            if(hist[c] >= 2) {
                rep(hist[c] - 1) {
                    extra.emplace_back(c);
                }
            }
        }
        // dbg(i, extra, need);

        if(isDebugging) {
            set<char> aux;
            for(auto& c: extra) aux.emplace(c);
            assert(sz(aux) == 0 || sz(aux) == 1);
        }

        assert(sz(extra) == sz(need));
        for(int j = 0; j < sz(extra); j++) {
            G[extra[j]][need[j]].emplace_back(i);
        }
    }
    // dbg(E);

    using Info = tuple<int, char, int, char>;
    vector<Info> response;

    auto add = [&](int i, char c1, int j, char c2) -> void {
        // dbg("add", i + 1, c1, j + 1, c2);
        response.emplace_back(i + 1, c1, j + 1, c2);

        // check and remove
        assert(E[i].find(c1) != E[i].end());
        E[i].erase(E[i].find(c1));

        assert(E[j].find(c2) != E[j].end());
        E[j].erase(E[j].find(c2));

        // add
        E[i].emplace(c2);
        E[j].emplace(c1);

        // check
        assert(sz(E[i]) == 3);
        assert(sz(E[j]) == 3);
    };

    // extra - need
    while(!G['w']['i'].empty()) {
        if(G['i']['w'].empty()) break;

        int i = G['w']['i'].back();
        int j = G['i']['w'].back();
        assert(i != j);
        G['w']['i'].pop_back();
        G['i']['w'].pop_back();

        add(i, 'w', j, 'i');
    }
    while(!G['w']['n'].empty()) {
        if(G['n']['w'].empty()) break;

        int i = G['w']['n'].back();
        int j = G['n']['w'].back();
        assert(i != j);
        G['w']['n'].pop_back();
        G['n']['w'].pop_back();

        add(i, 'w', j, 'n');
    }

    // for(auto& x: E) dbg(x);

    {
        vector<int> id_extra_w;
        vector<int> id_need_w;
        for(int i = 0; i < n; i++) {
            map<int, int> hist;
            for(auto& c: E[i]) hist[c]++;

            if(hist['w'] == 0) id_need_w.emplace_back(i);
            if(hist['w'] > 1) id_extra_w.emplace_back(i);
        }

        assert(sz(id_extra_w) == sz(id_need_w));

        for(int i = 0; i < sz(id_extra_w); i++) {
            int u = id_extra_w[i];
            char c1 = 'w';


            int v = id_need_w[i];
            map<char, int> hist;
            for(auto& x: E[v]) {
                hist[x]++;
            }

            char c2 = '?';
            for(auto& c: target) {
                if(hist[c] > 1) {
                    c2 = c;
                    break;
                }
            }
            assert(c2 != '?');

            add(u, c1, v, c2);
        }
    }

    if(isDebugging) {
        for(int i = 0; i < n; i++) {
            map<char, int> hist;
            for(auto& c: E[i]) hist[c]++;
            assert(hist['w'] == 1);
        }
    }

    vector<int> ii, nn;
    for(int i = 0; i < n; i++) {
        map<int, int> hist;
        for(auto& c: E[i]) {
            hist[c]++;
        }

        if(hist['i'] == 1 && hist['n'] == 1) {

        } else if(hist['i'] == 2) {
            ii.emplace_back(i);
        } else {
            assert(hist['n'] == 2);
            nn.emplace_back(i);
        }
    }
    assert(sz(ii) == sz(nn));

    for(int i = 0; i < sz(ii); i++) {
        add(ii[i], 'i', nn[i], 'n');
    }

    if(isDebugging) {
        bool ok = true;
        for(int i = 0; i < n; i++) {
            str cur;
            for(auto& c: E[i]) {
                cur.push_back(c);
            }
            sort(all(cur));
            assert(cur == "inw");
        }
        assert(ok);
    } else {
        cout << sz(response) << "\n";
        for(auto& [a1, c1, a2, c2]: response) {
            cout << a1 << " " << c1 << " " << a2 << " " << c2 << "\n";
        }
    }
}

void solve() {
    int n; cin >> n;
    V<str> S(n); for(auto& x: S) cin >> x;

    slv(n, S);
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
        int n = rng_ll(2, 1000);
        vector<int> cnt(3, n);
        string target = "win";

        vector<string> S(n, string(3, '?'));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 3; j++) {
                int id = -1;
                while(true) {
                    id = rng_ll(0, 2);
                    if(cnt[id] > 0) {
                        break;
                    }
                }
                cnt[id]--;

                S[i][j] = target[id];
            }
        }

        dbg(n);
        // for(auto& x: S) dbg(x);

        slv(n, S);
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
