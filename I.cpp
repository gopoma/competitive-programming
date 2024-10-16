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
//? /Template

ll tot_casos;
ll caso = 1;
void solve() {
    //? <>
    vs words;
    while(true) {
        str S; cin >> S; if(S == "*") break;
        words.eb(S);
    }    
    cin.ignore();
    dbg(words);

    V<pair<str, str>> queries;
    while(true) {
        str line;
        while(getline(cin, line)) {
            while(!line.empty() && line.bk == ' ') line.pop_back();
            if(line.empty()) break;

            int idxSpace = -1;
            const int N = sz(line);
            for(int i = 0; i < N; i++) if(line[i] == ' ') idxSpace = i;

            str from = line.substr(0, idxSpace);
            str to = line.substr(idxSpace + 1, (sz(line) - 1) - (idxSpace + 1) + 1);
            queries.eb(from, to);
        }
        if(line == "") break;
    }
    dbg(queries);
    //? V<pair<str, str>> edges;
    const int N = sz(words);
    map<str, vs> adj;
    for(int i = 0; i < N; i++) for(int j = i + 1; j < N; j++) {
        if(sz(words[i]) != sz(words[j])) continue;
        int diff = 0;
        const int M = sz(words[i]);
        for(int k = 0; k < M; k++) diff += (words[i][k] != words[j][k]);
        //? if(diff == 1) edges.eb(words[i], words[j]);
        if(diff == 1) {
            adj[words[i]].eb(words[j]);
            adj[words[j]].eb(words[i]);
        }
    }
    //? dbg(edges);
    //? for(auto& [u, v]: edges) cout << u << " " << v << "\n"; 
    for(auto& [from, to]: queries) {
        map<str, bool> vis; vis[from] = true;
        map<str, int> dist; dist[from] = 0;
        deque<str> q; q.eb(from);
        while(!q.empty()) {
            str x = q.ft; q.pop_front();
            each(nxt, adj[x]) {
                if(!vis[nxt]) {
                    vis[nxt] = true;
                    dist[nxt] = dist[x] + 1;
                    q.eb(nxt);
                }
            } 
        }
        cout << from << " " << to << " " << dist[to] << "\n";
    }
    if(caso == tot_casos) return;
    cout << "\n";
    caso++;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int t = 1; cin >> t;
    tot_casos = t;
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
