#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define tcT template<class T

using ll = long long;
using ld = long double;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;

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

const int N = 1e5;  // limit for array size
int n;  // array size
int tree[2 * N];

void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) tree[i] = tree[i<<1] + tree[i<<1|1];
}

void modify(int l, int r, int value) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) tree[l++] += value;
    if (r&1) tree[--r] += value;
  }
}

int query(int p) {
  int res = 0;
  for (p += n; p > 0; p >>= 1) {
    DBG2(p, tree[p]);
    res += tree[p];
  }
  return res;
}

void solve() {
    int q;
    cin >> n >> q;


    for(int i = 0; i < n; ++i) {
        scanf("%d", tree + n + i);
    }
    build();
    cout << "tree:\n";
    for(int i = 0; i < 2*n; i++)
        cout << tree[i] << " ";
    cout << n_l;


    for(int i = 1; i <= q; i++) {
        int type;
        cin >> type;

        assert(type == 1 || type == 2);
        if(type == 1) {
            int a, b, u; cin >> a >> b >> u;
            a--; b--;

            modify(a, b, u);
        } else {
            int k; cin >> k;
            k--;

            int ans = query(k);
            cout << ans << n_l;
        }
    }
    cout << "Final:\n";
    for(int i = 0; i < 2*n; i++) {
        cout << tree[i] << " ";
    }
    cout << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}