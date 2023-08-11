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

struct dsu {
    vector<int> par, rnk, size; int c;
    dsu(int n) : par(n+1), rnk(n+1,0), size(n+1,1), c(n) {
        for (int i = 1; i <= n; ++i) par[i] = i;
    }
    int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
    bool same(int i, int j) { return find(i) == find(j); }
    int get_size(int i) { return size[find(i)]; }
    int count() { return c; } //connected components
    int merge(int i, int j) {
        if ((i = find(i)) == (j = find(j))) return -1; else --c;
        if (rnk[i] > rnk[j]) swap(i, j);
        par[i] = j; size[j] += size[i];
        if (rnk[i] == rnk[j]) rnk[j]++;
        return j;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    vector<str> S(n);
    for(auto& s: S) cin >> s;

    vector<array<int, 3>> ed;
    for(int u = 0; u < n; u++) {
        for(int v = u+1; v < n; v++) {
            // S[i] and S[j]
            int w = 0;
            for(int p = 0; p < k; p++) {
                w += abs(S[u][p] - S[v][p]);
            }

            ed.pb({w, u, v});
            ed.pb({w, v, u});
        }
    }

    //* Kruskal's MST Algorithm
    sort(ed.begin(), ed.end());
    int ans = 0;
    dsu d(n);
    for (auto e: ed){
        int u = e[1], v = e[2], w = e[0];
        if (d.same(u, v)) continue;
        ans = max(ans, w);
        d.merge(u, v);
    }
    cout << ans << n_l;
    //* Kruskal's MST Algorithm
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
