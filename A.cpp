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

vl pResponse, qResponse;
bool checkBrute(ll n, vl a) {
    vl ptemp(n); iota(all(ptemp), 1LL);
    do {
        vl qtemp(n); iota(all(qtemp), 1LL);
        do {
            vl p = ptemp; p.insert(p.begin(), 0LL);
            vl q = qtemp; q.insert(q.begin(), 0LL);

            bool ok = true;
            for(int i = 1; i <= n; i++) {
                ok &= (p[i] != i);
                ok &= (q[i] != i);
                ok &= (i == a[p[q[i]]]);
            }
            if(ok) {
                pResponse = p;
                qResponse = q;
                return true;
            }
        } while(next_permutation(all(qtemp)));
    } while(next_permutation(all(ptemp)));
    return false;
}

V<vl> work(ll n, vl a) {
    vb vis(n + 1);
    V<vl> re;
    for(ll x = 1; x <= n; x++) {
        if(!vis[x]) {
            vl C;
            ll cur = x;
            while(!vis[cur]) {
                C.emplace_back(cur);

                vis[cur] = true;
                cur = a[cur];
            }
            re.emplace_back(C);
        }
    }
    return re;
}

bool check(ll n, vl a) {
    if(n <= 3) return checkBrute(n, a);
    else return true;
}

void slv(ll n, vl a) {
    if(n <= 3) {
        if(!isDebugging) {
            bool ok = checkBrute(n, a);
            if(!ok) {
                cout << "Impossible\n";
                return;
            }
            cout << "Possible\n";
            for(int i = 1; i <= n; i++) {
                cout << pResponse[i] << " ";
            }
            cout << "\n";
            for(int i = 1; i <= n; i++) {
                cout << qResponse[i] << " ";
            }
            cout << "\n";
        }
        return;
    }

    vl ip(n + 1);
    for(int i = 1; i <= n; i++) {
        ip[a[i]] = i;
    }
    vl op(n + 1);
    for(int i = 1; i <= n; i++) {
        op[i] = ip[i];
    }

    V<vl> components = work(n, op);
    // dbg(components);

    map<ll, ll> id;
    set<set<pair<ll, ll>>> S;
    map<ll, set<set<pair<ll, ll>>>::iterator> mp;
    map<ll, set<pair<ll, ll>>> currentState;
    map<ll, pair<ll, ll>> xd;

    for(auto& C: components) {
        ll mn = *min_element(all(C));
        ll idLeader = mn;

        set<pair<ll, ll>> current;
        set<ll> currentcurrent;
        ll cnt = 1;
        for(auto& x: C) {
            current.emplace(cnt, x);
            xd[x] = {cnt, x};
            currentcurrent.emplace(x);
            id[x] = idLeader;
            cnt++;
        }

        pair<set<set<pair<ll, ll>>>::iterator, bool> it = S.insert(current);
        mp[id[mn]] = it.first;
        currentState[id[mn]] = current;
    }

    // dbg(id);
    // dbg(S);
    // dbg(currentState);

    vl p(n + 1);
    vl q(n + 1);

    for(auto& C: components) {
        for(auto& x: C) {
            // RAYA;
            dbg(x);
            assert(!S.empty());
            auto current = mp[id[x]];
            // dbg(*current);
            if(sz(S) == 1) {
                current = S.begin();
            }


            assert(!(*S.begin()).empty());
            ll other = (*(*S.begin()).begin()).second;
            // dbg(other);
            // dbg(id[x], id[other]);
            if(sz(S) == 1 && (id[x] == id[other])) {
                dbg("sz(S) == 1");
                ll X = x;
                ll Y = ip[X];

                auto it = currentState[id[x]].lower_bound(xd[x]);
                // dbg(*current);
                ll oo = -1;
                while(true) {
                    if(it == currentState[id[x]].end()) {
                        it = currentState[id[x]].begin();
                    }
                    auto v = (*it).second;
                    if(v != X && v != Y) {
                        oo = v;
                        break;
                    }
                    it++;
                     if(it == currentState[id[x]].end()) {
                        it = currentState[id[x]].begin();
                    }
                }
                dbg(X, oo, Y);

                q[X] = oo;
                p[oo] = Y;

                currentState[id[oo]].erase(xd[oo]);
            } else {
                dbg("sz(S) > 1");

                auto nxt = current;
                if(sz(S) > 1) {
                    ll other = (*nxt).begin()->second;
                    if(id[x] != id[other]) {
                        dbg("id[x] != id[other]", id[x], id[other]);
                        nxt = current;
                    } else {
                        nxt = next(current);
                    }
                } else {
                    if(id[x] != id[other]) {
                        // dbg("id[x] != id[other]", id[x], id[other]);
                        nxt = current;
                    } else {
                        nxt = next(current);
                    }
                }
                if(nxt == S.end()) {
                    nxt = S.begin();
                }
                assert(nxt != S.end());
                dbg(*current);
                dbg(*nxt);

                ll X = x;
                ll oo = -1;
                ll Y = ip[X];


                auto it = currentState[id[(*(*nxt).begin()).second]].rbegin();
                // dbg(currentState[id[(*(*nxt).begin()).second]]);
                while(true) {
                    auto v = (*it).second;
                    if(v != X && v != Y) {
                        oo = v;
                        break;
                    }
                    it--;
                }


                dbg(X, oo, Y);
                q[X] = oo;
                p[oo] = Y;

                currentState[id[oo]].erase(xd[oo]);
                if(currentState[id[oo]].empty()) {
                    S.erase(mp[id[oo]]);
                }
            }
        }
    }

    if (isDebugging) {
        vl tar(n); iota(all(tar), 1LL);
        tar.insert(tar.begin(), 0LL);
        dbg(p);
        dbg(q);
        dbg(tar);

        vl P = p, Q = q;
        sort(all(P));
        sort(all(Q));
        assert(P == tar);
        assert(Q == tar);

        bool ok = true;
            for(int i = 1; i <= n; i++) {
                ok &= (p[i] != i);
                ok &= (q[i] != i);
                ok &= (i == a[p[q[i]]]);
            }
        assert(ok);
    } else {
        cout << "Possible\n";
        for(int i = 1; i <= n; i++) {
            cout << p[i] << " ";
        }
        cout << "\n";
        for(int i = 1; i <= n; i++) {
            cout << q[i] << " ";
        }
        cout << "\n";
    }

}

void solve() {
    ll n; cin >> n;
    vl a(n + 1);  for(int i = 1; i <= n; i++) cin >> a[i];
    dbg(n);
    dbg(a);

    slv(n, a);
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(1) {
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        ll n = rng_ll(1, 7);
        vl a(n); iota(all(a), 1LL);
        shuffle(all(a), rng);
        a.insert(a.begin(), 0);

        dbg(n, a);
        slv(n, a);
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
