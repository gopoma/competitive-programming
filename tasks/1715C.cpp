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

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

//* Template
//? https://codeforces.com/contest/2000/submission/276943782
//? 0-indexed
//? [l, r]

class SegmentTree {
private:
    std::vector<ll> seg;
    std::vector<ll> lazy;
    std::vector<ll> arr;
    int n;

    void build(ll node, ll st, ll en) {
        if (st == en) {
            seg[node] = arr[st];
            return;
        }

        ll mid = (st + en) / 2;

        // Llamada recursiva para el hijo izquierdo
        build(2 * node, st, mid);

        // Llamada recursiva para el hijo derecho
        build(2 * node + 1, mid + 1, en);

        // Actualización del nodo padre con los valores de los hijos
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }

    void update(ll node, ll st, ll en, ll l, ll r, ll val) {
        if (lazy[node] != 0) { // Si el nodo es "lazy", lo actualiza
            seg[node] += (en - st + 1) * lazy[node];

            if (st != en) { // Si los hijos existen, los marca como "lazy"
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0; // Ya no es "lazy"
        }

        if (en < l || st > r) { // Caso 1: fuera del rango
            return;
        }

        if (st >= l && en <= r) { // Caso 2: completamente dentro del rango
            seg[node] += (en - st + 1) * val;
            if (st != en) {
                lazy[2 * node] += val; // Marca a los hijos como "lazy"
                lazy[2 * node + 1] += val;
            }
            return;
        }

        // Caso 3: parcialmente dentro del rango
        ll mid = (st + en) / 2;

        // Llamada recursiva para actualizar el hijo izquierdo
        update(2 * node, st, mid, l, r, val);
        // Llamada recursiva para actualizar el hijo derecho
        update(2 * node + 1, mid + 1, en, l, r, val);

        // Actualización del nodo padre con los valores de los hijos
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }

    ll query(ll node, ll st, ll en, ll l, ll r) {
        if (lazy[node] != 0) { // Si el nodo es "lazy", lo actualiza
            seg[node] += (en - st + 1) * lazy[node];
            if (st != en) { // Verifica si los hijos existen
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0; // Ya no es "lazy"
        }

        if (en < l || st > r) { // Caso 1: fuera del rango
            return 0;
        }

        if (l <= st && en <= r) { // Caso 2: completamente dentro del rango
            return seg[node];
        }

        ll mid = (st + en) / 2;

        // Consulta del hijo izquierdo
        ll q1 = query(2 * node, st, mid, l, r);

        // Consulta del hijo derecho
        ll q2 = query(2 * node + 1, mid + 1, en, l, r);

        return q1 + q2;
    }

public:
    SegmentTree(ll size, std::vector<ll>& elements) {
        n = size;
        arr = elements;
        seg.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1);
    }
	// Constructor sin arreglo, inicializa todo a cero
    SegmentTree(ll size) {
        n = size;
        arr.assign(n, 0); // Inicializa el arreglo con ceros
        seg.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1);
    }
    void update(ll l, ll r, ll val) {
        update(1, 0, n - 1, l, r, val);
    }

    ll query(ll l, ll r) {
        return query(1, 0, n - 1, l, r);
    }
};
//* /Template

void solve() {
    ll n, m; cin >> n >> m;

    vl a(n + 1); for(int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<ll, ll>> que(m);
    for(auto& [i, x]: que) cin >> i >> x;

    dbg(n, m);
    dbg(a);
    dbg(que);

    vl d(n + 1);
    {
        ll current = -1;
        for(int i = 1; i <= n; i++) {
            if(a[i] != current) {
                d[i] = +1;
                current = a[i];
            }
        }
        dbg(d);

    }
    vl temp(n + 1, 0);
    SegmentTree st(n + 1, temp);
    for(int i = 1; i <= n; i++) {
        st.update(i, n, d[i]);
    }

    auto ddd = [&]() -> void {
        if(false) {
            vl tmp;
            for(int i = 1; i <= n; i++) {
                tmp.emplace_back(st.query(i, i));
            }
            dbg(tmp);
        }
    };

    auto calc = [&](ll i) -> ll {
        ll k = n - i + 1;
        ll res = st.query(i, n) - k * st.query(i - 1, i - 1);
        return res;
    };

    ll response = 0;
    for(int i = 1; i <= n; i++) {
        RAYA;
        ll contrib = calc(i);
        //* dbg(i, contrib);
        //* ddd();
        response += contrib;

        if(d[i] == 0) {
            response += (n - i + 1);
        }
    }
    dbg(response);

    auto check = [&](ll i) -> bool {
        return (1 <= i && i <= n);
    };

    for(auto& [i, x]: que) {
        RAYA;
        dbg(i, x);
        dbg(response);

        for(int delta = -1; delta <= +1; delta++) {
            if(check(i + delta)) {

                if(d[i + delta] == 0) {
                    response -= (n - (i + delta) + 1);
                } else {
                    ll k = (n - (i + delta) + 1);
                    response -= k * (i + delta);
                }
            }
        }
        //* for(int delta = -1; delta <= +1; delta++) {
        //*     if(check(i + delta)) {
        //*         st.update(i + delta, n, -d[i + delta]);
        //*     }
        //* }
        //* dbg(response);

        a[i] = x;
        d[i] = 1;
        if(check(i + 1)) {
            if(a[i] == a[i + 1]) {
                d[i + 1] = 0;
                d[i] = 1;
            } else {
                d[i + 1] = 1;
                d[i] = 1;
            }
        }

        if(check(i - 1)) {
            if(a[i - 1] == a[i]) {
                d[i] = 0;
            } else {
                d[i] = 1;
            }
        }
        dbg(a);
        dbg(d);

        //* for(int delta = -1; delta <= +1; delta++) {
        //*     if(check(i + delta)) {
        //*         st.update(i + delta, n, +d[i + delta]);
        //*     }
        //* }
        //* ddd();

        for(int delta = -1; delta <= +1; delta++) {
            if(check(i + delta)) {
                if(d[i + delta] == 0) {
                    response += (n - (i + delta) + 1);
                } else {
                    ll k = (n - (i + delta) + 1);
                    response += k * (i + delta);
                }
            }
        }

        cout << response << "\n";
    }
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1; //* cin >> t;
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
