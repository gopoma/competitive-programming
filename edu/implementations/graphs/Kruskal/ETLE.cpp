//!
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
//!

#include <bits/stdc++.h>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

using ll = long long;
using ld = long long;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!

#define mp  make_pair
#define f   first
#define s   second

#define sz(x)   int((x).size())
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

#define lb lower_bound
#define ub upper_bound

const int MOD = (int)1e9 + 7;   // 998244353;
const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};


void solve() {
    vector<Edge> edges;

    int n, k;
    cin >> n >> k;

    vector<str> S(n);
    for(auto& s: S) cin >> s;

    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            // S[i] and S[j]
            int cost = 0;
            for(int p = 0; p < k; p++) {
                cost += abs(S[i][p] - S[j][p]);
            }

            Edge forward = {i+1, j+1, cost};
            Edge backward = {j+1, i+1, cost};

            edges.eb(forward);
            edges.eb(backward);
        }
    }



    //* Kruskal's MST Algorithm
    int N = edges.size();

    int cost = 0;
    vector<int> tree_id(N);
    vector<Edge> result;
    for (int i = 0; i < N; i++) {
        tree_id[i] = i;
    }

    sort(edges.begin(), edges.end());

    for(Edge e: edges) {
        if(tree_id[e.u] != tree_id[e.v]) {
            cost += e.weight;
            result.push_back(e);

            int old_id = tree_id[e.u], new_id = tree_id[e.v];
            for(int i = 0; i < N; i++) {
                if(tree_id[i] == old_id) {
                    tree_id[i] = new_id;
                }
            }
        }
    }
    //* Kruskal's MST Algorithm



    int ans = 0;
    for(Edge& e: result) {
        ans = max(ans, e.weight);
    }
    cout << ans << n_l;
}

// Verification: https://redprogramacioncompetitiva.com/contests/2023/07/team/problem.php/
int main() {
    ios::sync_with_stdio(false);

    cin.tie(nullptr);
    ll t = 1;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
