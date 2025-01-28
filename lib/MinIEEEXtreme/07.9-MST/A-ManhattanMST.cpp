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
#define F   first
#define S   second

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

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < sz(v); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}



typedef complex<double> point;
namespace std {
    bool operator < (point p, point q) {
        if (real(p) != real(q)) return real(p) < real(q);
        return imag(p) < imag(q);
    }
};

istream &operator>>(istream &is, point &p) {
    double x, y;
    is >> x >> y;
    p = point(x, y);
    return is;
}

double dot(point p, point q)   { return real(conj(p) * q); }
double cross(point p, point q) { return imag(conj(p) * q); }
double EPS = 1e-8;
int sign(double x) {
    if (x < -EPS) return -1;
    if (x > +EPS) return +1;
    return 0;
}

struct union_find {
    vector<int> p;
    union_find(int n) : p(n, -1) { };
    bool unite(int u, int v) {
        if ((u = root(u)) == (v = root(v))) return false;
        if (p[u] > p[v]) swap(u, v);
        p[u] += p[v]; p[v] = u;
        return true;
    }
    bool find(int u, int v) { return root(u) == root(v); }
    int root(int u) { return p[u] < 0 ? u : p[u] = root(p[u]); }
    int size(int u) { return -p[root(u)]; }
};

double rectilinear_mst(vector<point> ps) {
  vector<int> id(ps.size()); iota(all(id), 0);
  struct edge { int src, dst; double weight; };
  vector<edge> edges;
  for (int s = 0; s < 2; ++s) {
    for (int t = 0; t < 2; ++t) {
      sort(all(id), [&](int i, int j) {
          return real(ps[i]-ps[j]) < imag(ps[j]-ps[i]);});
      map<double, int> sweep;
      for (int i: id) {
        for (auto it = sweep.lower_bound(-imag(ps[i]));
                  it != sweep.end(); sweep.erase(it++)) {
          int j = it->S;
          if (imag(ps[j] - ps[i]) < real(ps[j] - ps[i])) break;
          double d = abs(real(ps[i]-ps[j])) + abs(imag(ps[i]-ps[j]));
          edges.push_back({i, j, d}); // all nearest edges in 8 directions
        }
        sweep[-imag(ps[i])] = i;
      }
      for (auto &p: ps) p = point(imag(p), real(p));
    }
    for (auto &p: ps) p = point(-real(p), imag(p));
  }
  double cost = 0;
  sort(all(edges), [](edge a, edge b) { return a.weight < b.weight; });
  union_find uf(int(ps.size()));
  for (auto e: edges)
    if (uf.unite(e.src, e.dst))
      cost += e.weight;
  return cost;
}




void solve() {
    int n;
    cin >> n;

    vector<point> ps(n);
    for(auto& e: ps)
        cin >> e;

    ll ans = ll(rectilinear_mst(ps));
    ans *= 2LL;

    cout << ans;
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
